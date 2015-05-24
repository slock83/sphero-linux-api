/*************************************************************************
	Sphero  -  Wrapper implementing all sphero-linked features
								(like packet creation, emission, reception)
							 -------------------
	started                : 07/03/2015
 ************************************************************************/

//-------------------------------------------------------- System includes

#include <endian.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
using namespace std;
//--------------------------------------------------------- Local includes

#include "Sphero.hpp"
#include "packets/SpheroPacket.hpp"
#include "packets/Constants.hpp"
#include "packets/async/SpheroStreamingPacket.hpp"

typedef struct syncThreadParam{
	std::function<void(answerUnion_t*)> callback;
	Sphero* sphero;
	uint8_t seqNum;
} syncThreadParam;

//-------------------------------------------------------- Private methods

void* Sphero::monitorStream(void* sphero_ptr)
{
	Sphero* sphero = (Sphero*) sphero_ptr;
	int _bt_sock = sphero->_bt_socket;
	uint8_t buf;
	SpheroPacket* packet_ptr;

	for(;;)
	{
		if(recv(_bt_sock, &buf, sizeof(buf), MSG_PEEK) <= 0)
		{
			sphero->disconnect();
		}
		else
		{
			if(SpheroPacket::extractPacket(_bt_sock, sphero, &packet_ptr))
			{
				packet_ptr->packetAction();
			}
		}
	}

	return NULL;
}
//END monitorStream

void* Sphero::wait_seq(void* thread_params)
{
	syncThreadParam* threadParam = (syncThreadParam*) thread_params;

	uint8_t seqNum = threadParam->seqNum;
	Sphero* sphero = threadParam->sphero;
	std::function<void(answerUnion_t*)> callback = threadParam->callback;

	delete threadParam;

	struct timespec timer;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	timer.tv_sec = tv.tv_sec;
	timer.tv_nsec = tv.tv_usec * 1000;
	timer.tv_sec += NB_SEC_SYNC_BEFORE_FAILURE;

	pthread_mutex_lock(&(sphero->_mutex_syncpacket));
	int rc = 0;
	while(sphero->_seqNumberReceived[seqNum] == NULL && rc != ETIMEDOUT)
	{
		rc = pthread_cond_timedwait(
				&(sphero->_conditional_syncpacket), 
				&(sphero->_mutex_syncpacket), &timer);
	}

	answerUnion_t* answer = sphero->_seqNumberReceived[seqNum];
	sphero->_seqNumberReceived[seqNum] = NULL;
	pthread_mutex_unlock(&(sphero->_mutex_syncpacket));
	callback(answer);
	delete answer;
	return 0;
}

/**
 * @brief sendPacket : Send the specified packet to the Sphero
 * @param packet : The packet to send to the Sphero
 */
void Sphero::sendPacket(ClientCommandPacket& packet)
{
	ssize_t retour;
	if((retour = send(_bt_socket, packet.toByteArray(),  packet.getSize(), 0)) <= 0)
	{
		disconnect();
	}

	fsync(_bt_socket);

}//END sendPacket

void Sphero::sendAcknowledgedPacket(ClientCommandPacket& packet, 
		std::function<void(answerUnion_t*)> callback, uint8_t seqToWait){
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_mutex_lock(&_mutex_syncpacket);
	if(_seqNumberReceived[seqToWait] != NULL)
		_seqNumberReceived[seqToWait] = NULL;
	pthread_mutex_unlock(&_mutex_syncpacket);

	syncThreadParam* threadParam = new syncThreadParam();
	threadParam->sphero = this;
	threadParam->seqNum = seqToWait;
	threadParam->callback = callback;
	
	pthread_t thread;

	pthread_create(&thread, &attr, wait_seq, (void*) threadParam);
	pthread_attr_destroy(&attr);
	sendPacket(packet);
}

//------------------------------------------------ Constructors/Destructor


/**
 * @param btaddr : Device address (format : "XX:XX:XX:XX:XX:XX")
 * @param btcon : A pointer to the bluetooth connector
 */
Sphero::Sphero(char const* const btaddr, bluetooth_connector* btcon):
	_connected(false), _bt_adapter(btcon), _address(btaddr),
	_seq(0), _resetTimer(true), _waitConfirm(false)
{
	pthread_mutex_init(&lock, NULL);
	_data = new DataBuffer();
	_mutex_syncpacket = PTHREAD_MUTEX_INITIALIZER;
	_mutex_seqNum = PTHREAD_MUTEX_INITIALIZER;
	_conditional_syncpacket = PTHREAD_COND_INITIALIZER;
	_seqNumberReceived = new answerUnion_t* [256];
	_syncTodo = new pendingCommandType[256];
	for(size_t i = 0 ; i < 256 ; i++)	
	{
		_seqNumberReceived[i++] = NULL;
		_syncTodo[i] = NONE;
	}
}


Sphero::~Sphero()
{
	delete _data;
	disconnect();
	delete _bt_adapter;
	

	for(size_t i = 0 ; i < 256 ; i++)
	{
		if(_seqNumberReceived[i] != NULL)
		{
			delete(_seqNumberReceived[i]);
		}
	}

	pthread_cond_destroy(&_conditional_syncpacket);
	pthread_mutex_destroy(&_mutex_seqNum);
	pthread_mutex_destroy(&_mutex_syncpacket);
	delete[] _seqNumberReceived;

}//END destructor


//--------------------------------------------------------- Public methods
/**
 * @brief : notify sphero that a synchronous packet has arrived
 *
 * @return nothing since it's a void method :-)
 */
void Sphero::notifySyncPacket(uint8_t seqId, answerUnion_t* pointer)
{
	pthread_mutex_lock(&_mutex_syncpacket);
	_seqNumberReceived[seqId] = pointer;
	pthread_cond_broadcast(&_conditional_syncpacket);
	pthread_mutex_unlock(&_mutex_syncpacket);
}

/**
 * @brief connect : Initializes the bluetooth connection to the sphero instance
 * @return true if the connection was successful, false otherwise
 */
bool Sphero::connect()
{
	disconnect();

	size_t i = 0;
	while((_bt_socket = _bt_adapter->connection(_address.c_str())) == -1 &&
		  i++ < MAX_CONNECT_ATTEMPT)
	{
	}

	if(_bt_socket != -1)
	{
		pthread_create(&monitor, NULL, monitorStream, this);

		_connected = true;
		_connect_handler.reportAction();

		return true;
	}

	return false;
}//END connect


/**
 * @brief disconnect : Disconnects the current Sphero
 */
void Sphero::disconnect()
{
#ifdef MAP
	fprintf(stderr, "Logging out\n");
#endif

	if(_connected)
	{
		_connected = false;
		pthread_cancel(monitor);
		_bt_adapter->disconnect();

		_disconnect_handler.reportAction();
	}
}//END disconnect




/**
 * @brief ping : Creates a ping request to the Sphero
 */
void Sphero::ping()
{
	ClientCommandPacket packet = ClientCommandPacket(
				DID::core,
				CID::ping,
				flags::notNeeded,
				0x01,
				NULL,
				true,
				true
				);
	sendPacket(packet);
}//END ping


/**
 * @brief setColor : Changes the Sphero light color
 * @param red : level of red (between 0x00 and 0xFF)
 * @param green : level of green (between 0x00 and 0xFF)
 * @param blue : level of blue (between 0x00 and 0xFF)
 * @param persist : true if you want the color to be defined as user color
 */
void Sphero::setColor(uint8_t red, uint8_t green, uint8_t blue, bool persist)
{
	uint8_t data_payload[4];
	data_payload[0] = red;
	data_payload[1] = green;
	data_payload[2] = blue;
	if (persist)
		data_payload[3] = 1;
	else
		data_payload[3] = 0;

	ClientCommandPacket packet (
				DID::sphero,
				CID::setRGBLEDOutput,
				flags::notNeeded,
				0x05,
				data_payload,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END setColor


/**
 * Commentez-les tous ! (feat Sacha)
 */

void Sphero::getColor(void (*callback)(ColorStruct*))
{
	pthread_mutex_lock(&_mutex_seqNum);
	uint8_t currentSeq = _seq++;
	pthread_mutex_unlock(&_mutex_seqNum);

	_syncTodo[currentSeq] = GETCOLOR;

	ClientCommandPacket packet(
				DID::sphero,
				CID::setBackLEDOutput,
				currentSeq,
				0x01,
				nullptr,
				true,
				_resetTimer
				);
	auto localWrapper = [callback](answerUnion_t* retour){
		ColorStruct* color = NULL;
		if(retour != NULL)
			color = new ColorStruct(*(retour->color));	
		callback(color);
	};
	sendAcknowledgedPacket(packet, localWrapper, currentSeq);
}

/**
 * @brief setBackLedOutput : Lights the back led(used to calibrate
 * 							 the spero direction) with the given power
 * @param power : The power the LED will receive
 */
void Sphero::setBackLedOutput(uint8_t power)
{
	ClientCommandPacket packet(
				DID::sphero,
				CID::setBackLEDOutput,
				flags::notNeeded,
				0x02,
				&power,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END setBackLedOutput


/**
 * @brief setHeading : Change the heading angle
 * @param heading : the new angle, in ° (range from 0 to 359)
 *	WARNING : Only use with 0. Effect: set the actual heading angle to 0
 */
void Sphero::setHeading(uint16_t heading)
{
	uint8_t data[2];
	uint8_t* ptr = (uint8_t*) &heading;
	data[0] = ptr[1];
	data[1] = ptr[0];

	ClientCommandPacket packet(
				DID::sphero,
				CID::setHeading,
				flags::notNeeded,
				0x03,
				data,
				_waitConfirm,
				_resetTimer
				);

	sendPacket(packet);
}//END setHeading


/**
 * @brief setStabilization : Enable or disable stabilization
 * @param on : enables if true, disables otherwise
 */
void Sphero::setStabilization(bool on)
{
	uint8_t state;
	state = on ? 1 : 0;

	ClientCommandPacket packet (
				DID::sphero,
				CID::setStabilization,
				flags::notNeeded,
				0x02,
				&state,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END setStabilization


/**
 * @brief setRotationRate : Change the rotation speed
 * @param angspeed : The new rotation speed (new speed will be angspeed*0.784 degrees/sec)
 *		Warning :=: high value may become really uncontrollable
 */
void Sphero::setRotationRate(uint8_t angspeed)
{
	ClientCommandPacket packet(
				DID::sphero,
				CID::setRotationRate,
				flags::notNeeded,
				0x02,
				&angspeed,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END setRotationRate


/**
* @brief setSelfLevel : This command controls the self level routine.
*			The self level routine attempts to achieve a horizontal orientation
*			where pitch and roll angles are less than the provided Angle Limit
*		After both angle limits are satisfied, option bits control sleep, final
*			angle (heading), and control system on/off. An asynchronous message
*			is returned when the self level routine completes (only when started
*			by API call)
*
* @param options : Flags to control the routine behavior. Disponible flags are:
*			Start/stop bit (only one of them can be used at a time):
*				START_ROUTINE : starts the routine
*				ABORT_ROUTINE : aborts the routine if in progress
*
*			Final angle bit:
*				CHECK_ANGLE : rotates to heading equal to beginning heading
*
*			Sleep bit:
*				SLEEP_AFTER_FINISH : The Sphero goes to sleep after leveling if used
*
*			Control System bit:
*				KEEP_CONTROL_SYSTEM : leaves control system on after leveling
*
* @param angle_limit : The max angle for completion (in degrees).
*			0 : Use the default value
*			Bounds : Between 1 and 90
*
* @param timeout : Set maximum seconds to run the routine
*			0 : Use the default value
*			Bounds : Between 1 and 255
*
* @param trueTime : Set the required “test for levelness” time to
*					10*<True Time> (in milliseconds)
*			0 : Use the default value
*			Bounds : Between 1 and 255
*/
void Sphero::setSelfLevel(uint8_t options, uint8_t angle_limit,
						  uint8_t timeout, uint8_t trueTime)
{
	uint8_t data_payload[4];
	data_payload[0] = options;
	data_payload[1] = angle_limit;
	data_payload[2] = timeout;
	data_payload[3] = trueTime;

	ClientCommandPacket packet(
				DID::sphero,
				CID::selfLevel,
				flags::notNeeded,
				0x05,
				data_payload,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END setSelfLevel


/**
 * @brief enableCollisionDetection : Enables the onBoard collision detector
 * @param Xt : An 8-bit settable threshold for the X (left/right) axis of Sphero
 *			A value of 0x00 disables the contribution of this axis
 *
 * @param Xspd : An 8-bit settable speed value for the X axis. This setting is
 *			ranged by the speed, then added to Xt to generate the final threshold value.
 *
 * @param Yt : An 8-bit settable threshold for the Y (front/back) axis of Sphero
 *			A value of 0x00 disables the contribution of this axis
 *
 * @param Yspd : An 8-bit settable speed value for the Y axis. This setting is
 *			ranged by the speed, then added to Yt to generate the final threshold value.
 *
 * @param Dead : An 8-bit post-collision dead time to prevent retriggering; specified in
 *			10ms increments.
 */
void Sphero::enableCollisionDetection(uint8_t Xt, uint8_t Xspd,
									  uint8_t Yt,  uint8_t Yspd,  uint8_t Dead)
{
	uint8_t data_payload[6];
	data_payload[0] = 0x01;
	data_payload[1] = Xt;
	data_payload[2] = Xspd;
	data_payload[3] = Yt;
	data_payload[4] = Yspd;
	data_payload[5] = Dead;

	ClientCommandPacket packet(
				DID::sphero,
				CID::configureCollisionDetection,
				flags::notNeeded,
				0x07,
				data_payload,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END enableCollisionDetection


/**
 * @brief disableCollisionDetection : Disables the onBoard collision detector
 */
void Sphero::disableCollisionDetection()
{
	uint8_t data_payload[6];
	data_payload[0] = 0x00;
	data_payload[1] = 0;
	data_payload[2] = 0;
	data_payload[3] = 0;
	data_payload[4] = 0;
	data_payload[5] = 0;

	ClientCommandPacket packet(
				DID::sphero,
				CID::configureCollisionDetection,
				flags::notNeeded,
				0x07,
				data_payload,
				_waitConfirm,
				_resetTimer);
	sendPacket(packet);
}//END disableCollisionDetection


/**
 * @brief isConnected : Checks the Sphero's connection state
 * @return true if it is connected.
 */
bool Sphero::isConnected()
{
	return _bt_adapter->isConnected();
}//END isConnected


/**
 * @brief configureLocator : Configure sphero's internal location
 * 							 calculation unit offsets
 * @param flags
 *			FLOATING_Y_AXIS : the Y axis won't be memorized, so heading 0 will do nothing
 * @param X : The current position on X axis of Sphero on the ground plane (in centimeters)
 * @param Y : The current position on Y axis of Sphero on the ground plane (in centimeters)
 * @param yaw : (yaw tare) Controls how the X,Y-plane is aligned with Sphero’s heading coordinate system.
 *			When this parameter is set to zero, it means that having yaw = 0 corresponds to facing down the Y-axis
 *																						 in the positive direction
 *			The value will be interpreted in the range 0-359 inclusive.
 */
void Sphero::configureLocator(uint8_t flags, uint16_t X, uint16_t Y, uint16_t yaw)
{
	uint8_t XA = (uint8_t)((X & 0xFF00) >> 8);
	uint8_t XB = (uint8_t)(X & 0x00FF);
	uint8_t YA = (uint8_t)((Y & 0xFF00) >> 8);
	uint8_t YB = (uint8_t)(Y & 0x00FF);
	uint8_t yawA = (uint8_t)((yaw & 0xFF00) >> 8);
	uint8_t yawB = (uint8_t)(yaw & 0x00FF);
	uint8_t data_payload[7];
	data_payload[0] = flags;
	data_payload[1] = XA;
	data_payload[2] = XB;
	data_payload[3] = YA;
	data_payload[4] = YB;
	data_payload[5] = yawA;
	data_payload[6] = yawB;

	ClientCommandPacket packet(
				DID::sphero,
				CID::configureLocator,
				flags::notNeeded,
				0x08,
				data_payload,
				_waitConfirm,
				_resetTimer);
	sendPacket(packet);
}

/**
 * @brief setDataStreaming : Enables sphero data streaming
 * @param freq : The sampling frequency
 * @param delay : The number of frames collected before sending
 * @param mask : A mask, to specify wanted values (view constants mask::*)
 * @param packetCount : The total number of repsonse packets the sphero will send (0 means infinite)
 * @param mask2 : (Optional) A mask, to specify wanted values (view constants mask2::*)
 */
void Sphero::setDataStreaming(uint16_t freq, uint16_t delay, uint32_t mask, uint8_t packetCount, uint32_t mask2)
{
	uint16_t M = 400 / freq;
	byte dlen = (mask2 == 0) ? 0x0a : 0x0e;

	uint8_t data[dlen];
	data[0] = M >> 8;
	data[1] = M;

	data[2] = delay >> 8;
	data[3] = delay;

	data[4] = mask >> 24;
	data[5] = mask >> 16;
	data[6] = mask >> 8;
	data[7] = mask;

	data[8] = packetCount;

	if(mask2)
	{

		data[9] = mask2 >> 24;
		data[10] = mask2 >> 16;
		data[11] = mask2 >> 8;
		data[12] = mask2;
	}

	ClientCommandPacket packet(
				DID::sphero,
				CID::setDataStreaming,
				flags::notNeeded,
				dlen,
				data,
				_waitConfirm,
				_resetTimer);
	sendPacket(packet);
	updateParameters(delay, mask, mask2);
}


/**
 * @return The sphero's DataBuffer instance
 */
DataBuffer* Sphero::getDataBuffer()
{
	return _data;
}


/**
 * @brief setAccelerometerRange : change sphero's accelerometer range,
 * 								warning : may cause strange behaviors
 * @param range : 	The accelerometer range. Use one (and only one!) of
 * 				  	the next flags to set the right range
 *					Any other value will have indeterminate consequences
 *					for driving and collision detection
 *
 *				ACC_2G : ±2Gs
 *				ACC_4G : ±4Gs
 *				ACC_8G : ±8Gs (default)
 *				ACC_16G : ±16Gs
 */
void Sphero::setAccelerometerRange(uint8_t range)
{
	ClientCommandPacket packet(
				DID::sphero,
				CID::setAccelerometerRange,
				flags::notNeeded,
				0x02,
				&range,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END setAccelerometerRange


/**
 * @brief roll : Defines a new heading angle and a new rotation speed
 * @param speed : The new rotation speed (new speed will be speed*0.784 degrees/sec)
 * @param heading : the new angle, in ° (range from 0 to 359)
 * @param state : In the CES firmware, this was used to gate the
 *			control system to either obey the roll vector or ignore it and apply optimal
 *			braking to zero speed
 */
void Sphero::roll(uint8_t speed, uint16_t heading, uint8_t state)
{
	uint8_t msb = (uint8_t)((heading & 0xFF00) >> 8);
	uint8_t lsb = (uint8_t)(heading & 0x00FF);
	uint8_t data_payload[4];
	data_payload[0] = speed;
	data_payload[1] = msb;
	data_payload[2] = lsb;
	data_payload[3] = state;

	ClientCommandPacket packet(
				DID::sphero,
				CID::roll,
				flags::notNeeded,
				0x05,
				data_payload,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}//END roll


/**
 * @brief setInactivityTimeout :To save battery power, Sphero normally goes to sleep after a period of inactivity.
 * @param timeout : Time before Sphero goes to sleep (when nothing happens), in seconds
 *			From the factory this value is set to 600 seconds (10 minutes)
 *			The inactivity timer is reset every time an API command is received over Bluetooth or a shell
 *																			command is executed in User Hack mode.
 *			In addition, the timer is continually reset when a macro is running unless the MF_STEALTH
 *										flag is set, and the same for orbBasic unless the BF_STEALTH flag is set.
 */
void Sphero::setInactivityTimeout(uint16_t timeout)
{
	if(timeout < 60)
	{
		timeout = 60;
	}
	timeout = htobe16(timeout);
	uint8_t* data = (uint8_t*) &timeout;

	ClientCommandPacket packet(
				DID::core,
				CID::setInactivityTimeout,
				flags::notNeeded,
				0x03,
				data,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);
}


/**
 * @brief updateParameters : Updates the parameters to check on reception
 * @param nbFrames : the number of frames per packet
 * @param mask : The data mask
 * @param mask2 : The data second mask
 */
void Sphero::updateParameters(int nbFrames, uint32_t maskVal, uint32_t mask2Val)
{
	_nbFrames = nbFrames;

	pthread_mutex_lock(&lock);

	_typesLst.clear();

	if(maskVal & mask::RAW_ACCEL_X)
		_typesLst.push_back(dataTypes::RAW_ACCEL_X);

	if(maskVal & mask::RAW_ACCEL_Y)
		_typesLst.push_back(dataTypes::RAW_ACCEL_Y);

	if(maskVal & mask::RAW_ACCEL_Z)
		_typesLst.push_back(dataTypes::RAW_ACCEL_Z);

	if(maskVal & mask::RAW_GYRO_X)
		_typesLst.push_back(dataTypes::RAW_GYRO_X);

	if(maskVal & mask::RAW_GYRO_Y)
		_typesLst.push_back(dataTypes::RAW_GYRO_Y);

	if(maskVal & mask::RAW_GYRO_Z)
		_typesLst.push_back(dataTypes::RAW_GYRO_Z);

	if(maskVal & mask::RAW_RIGHT_MOTOR_BACK_EMF)
		_typesLst.push_back(dataTypes::RAW_RIGHT_MOTOR_BACK_EMF);

	if(maskVal & mask::RAW_LEFT_MOTOR_BACK_EMF)
		_typesLst.push_back(dataTypes::RAW_LEFT_MOTOR_BACK_EMF);

	if(maskVal & mask::RAW_LEFT_MOTOR_PWM)
		_typesLst.push_back(dataTypes::RAW_LEFT_MOTOR_PWM);

	if(maskVal & mask::RAW_RIGHT_MOTOR_PWM)
		_typesLst.push_back(dataTypes::RAW_RIGHT_MOTOR_PWM);

	if(maskVal & mask::FILTERED_PITCH_IMU)
		_typesLst.push_back(dataTypes::FILTERED_PITCH_IMU);

	if(maskVal & mask::FILTERED_ROLL_IMU)
		_typesLst.push_back(dataTypes::FILTERED_ROLL_IMU);

	if(maskVal & mask::FILTERED_YAW_IMU)
		_typesLst.push_back(dataTypes::FILTERED_YAW_IMU);

	if(maskVal & mask::FILTERED_ACCEL_X)
		_typesLst.push_back(dataTypes::FILTERED_ACCEL_X);

	if(maskVal & mask::FILTERED_ACCEL_X)
		_typesLst.push_back(dataTypes::FILTERED_ACCEL_X);

	if(maskVal & mask::FILTERED_ACCEL_Y)
		_typesLst.push_back(dataTypes::FILTERED_ACCEL_Y);

	if(maskVal & mask::FILTERED_ACCEL_Z)
		_typesLst.push_back(dataTypes::FILTERED_ACCEL_Z);

	if(maskVal & mask::FILTERED_RIGHT_MOTOR_BACK_EMF)
		_typesLst.push_back(dataTypes::FILTERED_RIGHT_MOTOR_BACK_EMF);

	if(maskVal & mask::FILTERED_LEFT_MOTOR_BACK_EMF)
		_typesLst.push_back(dataTypes::FILTERED_LEFT_MOTOR_BACK_EMF);

	if(mask2Val & mask2::QUATERNION_Q0)
		_typesLst.push_back(dataTypes::QUATERNION_Q0);

	if(mask2Val & mask2::QUATERNION_Q1)
		_typesLst.push_back(dataTypes::QUATERNION_Q1);

	if(mask2Val & mask2::QUATERNION_Q2)
		_typesLst.push_back(dataTypes::QUATERNION_Q2);

	if(mask2Val & mask2::QUATERNION_Q3)
		_typesLst.push_back(dataTypes::QUATERNION_Q3);

	if(mask2Val & mask2::ODOMETER_X)
		_typesLst.push_back(dataTypes::ODOMETER_X);

	if(mask2Val & mask2::ODOMETER_Y)
		_typesLst.push_back(dataTypes::ODOMETER_Y);

	if(mask2Val & mask2::ACCELONE_0)
		_typesLst.push_back(dataTypes::ACCELONE_0);

	if(mask2Val & mask2::VELOCITY_X)
		_typesLst.push_back(dataTypes::VELOCITY_X);

	if(mask2Val & mask2::VELOCITY_Y)
		_typesLst.push_back(dataTypes::VELOCITY_Y);

	sort(_typesLst.begin(), _typesLst.end());

	pthread_mutex_unlock(&lock);

}

const vector<dataTypes> Sphero::getTypesList()
{
	return _typesLst;
}


/**
 * @brief checkValid : Checks the validity of a packet length
 * @param len : The packet length
 * @return true if the length matches with the current parameters
 */
bool Sphero::checkValid(int len)
{
	bool valid = false;
	if((unsigned int)len - 1 == _typesLst.size() * 2 * _nbFrames)
		valid = true;

	return valid;
}

/**
 * @brief requestLock : Requests the mutex to use the types list
 * @param take : if true, the lock will be taken. Otherwise, it will be released
 */
void Sphero::requestLock(bool take)
{
	if(take)
		pthread_mutex_lock(&lock);
	else
		pthread_mutex_unlock(&lock);
}


/**
 * @brief sleep : This command puts Sphero to sleep immediately
 * @param time : The number of seconds for Sphero to sleep for and then automatically reawaken.
 *			Zero does not program a wakeup interval, so he sleeps forever.
 *			0xFFFF attempts to put him into deep sleep (if supported in hardware)
 *									and returns an error if the hardware does not support it.
 * @param macro : If non-zero, Sphero will attempt to run this macro ID upon wakeup.
 * @param orbbasic : If non-zero, Sphero will attempt to run an orbBasic program in Flash from this line number.
 */
void Sphero::sleep(uint16_t time, uint8_t macro, uint16_t orbbasic)
{
	uint8_t msbTime = (uint8_t)((time & 0xFF00) >> 8);
	uint8_t lsbTime = (uint8_t)(time & 0x00FF);
	uint8_t msbOrb = (uint8_t)((orbbasic & 0xFF00) >> 8);
	uint8_t lsbOrb = (uint8_t)(orbbasic & 0x00FF);
	uint8_t data_payload[5];
	data_payload[0] = msbTime;
	data_payload[1] = lsbTime;
	data_payload[2] = macro;
	data_payload[3] = msbOrb;
	data_payload[4] = lsbOrb;

	ClientCommandPacket packet(
				DID::core,
				CID::sleep,
				flags::notNeeded,
				0x06,
				data_payload,
				_waitConfirm,
				_resetTimer
				);
	sendPacket(packet);

}//END sleep

/*
//setRawMotorValue : not needed ?

void Sphero::setMotionTimeout(uint16_t time);

void Sphero::setPermOptFlags(uint32_t flags);

//getPermOptFlags : we'll see

void Sphero::setTmpOptFlags(uint32_t flags);

//getTmpOptFlags : we'll see

void Sphero::setDeviceMode(uint8_t value = 0);
//01h will set to user hack mode,
// will implement when we will know the usage of this mode

//getDeviceMode

void Sphero::runMacro(uint8_t id);

//void saveMacro(Macro macro);
*/

/**
 * @brief onConnect : Event thrown on Sphero connection
 * @param callback : The callback function to assign to this event
 *			Return type : void
 *			Parameters : none (void)
 */
void Sphero::onConnect(callback_connect_t callback)
{
	_connect_handler.addActionListener(callback);
}//END onConnect


/**
 * @brief onDisconnect : Event thrown on Sphero disconnection
 * @param callback : The callback function to assign to this event
 *			Return type : void
 *			Parameters : none (void)
 */
void Sphero::onDisconnect(callback_disconnect_t callback)
{
	_disconnect_handler.addActionListener(callback);
}//END onDisconnect


/**
 * @brief onPreSleep : Event thrown 10 sec. before sphero sleeps
 * @param callback : The callback function to assign to this event
 *			Return type : void
 *			Parameters : none (void)
 */
void Sphero::onPreSleep(callback_preSleep_t callback)
{
	_preSleep_handler.addActionListener(callback);
} //END onPreSleep


/**
 * @brief onCollision : Event thrown when the Sphero detects a collision
 * @param callback : The callback function to assign to this event
 *			Return type : void
 *			Parameters : spherocoord_t xCoord, spherocoord_t yCoord
 */
void Sphero::onCollision(callback_collision_t callback)
{
	_collision_handler.addActionListener(callback);
}


/**
 * @brief onData : Event thrown when the Sphero receives a data stream packet
 * @param callback : The callback function to assign to this event
 *			Return type : void
 *			Parameters : none (void)
 */
void Sphero::onData(callback_data_t callback)
{
	_data_handler.addActionListener(callback);
}


/**
 * @brief reportData : Exterior accessor for reporting a new collision
 */
void Sphero::reportCollision(CollisionStruct* infos)
{
	_collision_handler.reportAction(infos);
}


/**
 * @brief reportData : Exterior accessor for reporting a new data from stream
 */
void Sphero::reportData()
{
	_data_handler.reportAction();
}
