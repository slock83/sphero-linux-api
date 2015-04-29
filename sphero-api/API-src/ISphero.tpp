/*************************************************************************
 sphero  -  description
 -------------------
 début                : 7 avr. 2015
 copyright            : (C) 2015 par slock -- euhhhhh ... disons cela...
 *************************************************************************/

//---------- Réalisation de la tâche <sphero> (fichier Sphero.tpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <endian.h>
//------------------------------------------------------ Include personnel

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

/*
 * BT address (format : "XX:XX:XX:XX:XX:XX")
 */
Sphero::Sphero(char const* const btaddr) {
	_btManager = new T();
	address = btaddr;
	_btManager->connection(btaddr);
}



Sphero::~Sphero()
{
	//TODO : implement destructor
}

void Sphero::reconnect()
{
	_btManager->connection(address);
}

void Sphero::disconnect()
{
	_btManager->disconnect();
}

void Sphero::sendPacket(ClientCommandPacket packet)
{
	_btManager->send_data(packet.getSize(), packet.toByteArray());
}

void Sphero::ping()
{
	ClientCommandPacket packet = ClientCommandPacket(
		0x00,
		0x01,
		0x00,
		0x01,
		NULL,
		true,
		true
	);
	_btManager->send_data(packet.getSize(), packet.toByteArray());
}

void Sphero::setColor(uint8_t red, uint8_t green,
		uint8_t blue, bool persist)
//Changes the color with the given hex values, persist will set as user color
//02h 	20h 	<any> 	05h 	<value> 	<value> 	<value> 	<bool>
{
	uint8_t data_payload[4];
	data_payload[0] = red;
	data_payload[1] = green;
	data_payload[2] = blue;
	if (persist)
		data_payload[3] = 1;
	else
		data_payload[3] = 0;
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x20, 
			0x00, 
			0x05,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::setBackLedOutput(uint8_t power)
//change the light intensity of the back led
//02h 	21h 	<any> 	02h 	<value>
{
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x21, 
			0x00, 
			0x02,
			&power, 
			waitConfirm, 
			resetTimer
		);
	_btManager->send_data(packet->getSize(),packet->toByteArray());

	delete packet;
}

void Sphero::setHeading(uint16_t heading)
//Change the heading with and angle in ° (range from 0 to 359)
//02h 	01h 	<any> 	03h 	16-bit val
{
	uint8_t data[2];
	uint8_t* ptr = (uint8_t*) &heading;
	data[0] = ptr[1];
	data[1] = ptr[0];

	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x01, 
			0x00, 
			0x03,
			data, 
			waitConfirm, 
			resetTimer
		); 

	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::setStabilization(bool on)
//Enable or disable stabilization
//02h 	02h 	<any> 	02h 	<bool>
{
	uint8_t state;
	state = on ? 1 : 0;
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x02, 
			0x00, 
			0x02,
			&state, 
			waitConfirm, 
			resetTimer
		); 
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::setRotationRate(uint8_t angspeed)
//Change the rotation speed, as angspeed*0.784 degrees/sec
//Warning = high value may become really uncontrollable
//02h 	03h 	<any> 	02h 	<value>
{
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x03, 
			0x00, 
			0x02,
			&angspeed, 
			waitConfirm, 
			resetTimer
		); 
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::setSelfLevel(uint8_t options,
		uint8_t angle_limit, uint8_t timeout, uint8_t trueTime)
/**02h 	09h 	<any> 	05h 	<byte> 	<byte> 	<byte> 	<byte>

This command controls the self level routine. The self level routine attempts to 
achieve a horizontal orientation where pitch and roll angles are less than the 
provided Angle Limit. After both angle limits are satisfied, option bits control 
sleep, final angle (heading), and control system on/off. An asynchronous message 
is returned when the self level routine completes (only when started by API 
call). The required parameters are:
Name 	Value 	Description
Start/Stop Bit 0 0 aborts the routine if in progress. 1 starts the routine.
Final Angle Bit 1 0 just stops. 1 rotates to heading equal to beginning heading.
Sleep Bit 2 0 stays awake after leveling. 1 goes to sleep after leveling.
Control System 	Bit 3 0 leaves control system off. 1 leaves control system on 
(after leveling).

Angle Limit 	0 Use the default value
				1 to 90 Set the max angle for completion (in degrees)
Timeout 	0 Use the default value
			1 to 255 Set maximum seconds to run the routine
True Time 	0 Use the default value
			1 to 255 Set the required “test for levelness” time to 10*True Time 
			(in milliseconds) **/
{
	uint8_t data_payload[4];
	data_payload[0] = options;
	data_payload[1] = angle_limit;
	data_payload[2] = timeout;
	data_payload[3] = trueTime;
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x09, 
			0x00, 
			0x05,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}


//void Sphero::setDataStreaming(uint16_t N, uint16_t M,uint32_t MASK, uint8_t 
//pcnt, uint32_t MASK2 = 0); not used yet

void Sphero::enableCollisionDetection(uint8_t Xt,
		uint8_t Xspd, uint8_t Yt, uint8_t Yspd, uint8_t Dead)
//02h 	12h 	<any> 	07h 	<val> 	<val> 	<val> 	<val> 	<val> 	<val>
/**Xt, Yt 	An 8-bit settable threshold for the X (left/right) and Y 
 * (front/back) axes of Sphero. A value of 00h disables the contribution of that 
 * axis.
Xspd, Yspd 	An 8-bit settable speed value for the X and Y axes. This setting is 
ranged by the speed, then added to Xt, Yt to generate the final threshold value.
Dead 	An 8-bit post-collision dead time to prevent retriggering; specified in 
10ms increments.**/
{
	uint8_t data_payload[6];
	data_payload[0] = 0x01;
	data_payload[1] = Xt;
	data_payload[2] = Xspd;
	data_payload[3] = Yt;
	data_payload[4] = Yspd;
	data_payload[5] = Dead;
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x12, 
			0x00, 
			0x07,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::disableCollisionDetection()
//pretty self-explanatory
{
	uint8_t data_payload[6];
	data_payload[0] = 0x00;
	data_payload[1] = 0;
	data_payload[2] = 0;
	data_payload[3] = 0;
	data_payload[4] = 0;
	data_payload[5] = 0;
	ClientCommandPacket* packet = new ClientCommandPacket(0x02, 0x12, 0x00, 0x07,
			data_payload, waitConfirm, resetTimer);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::configureLocator(uint8_t flags, uint16_t X,
		uint16_t Y, uint16_t yaw)
//02h 	13h 	<any> 	02h 	<8 bit val> 	<16 bit signed val> 	<16 bit 
//signed val> 	<16 bit signed val>
//Configure sphero's internal location calculation unit offsets
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
	ClientCommandPacket* packet = new ClientCommandPacket(0x02, 0x13, 0x00, 0x08,
			data_payload, waitConfirm, resetTimer);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

//getLocator : will have to discuss this...
//getRGDLed : same

void Sphero::setAccelerometerRange(uint8_t range)
//02h 	14h 	<any> 	02h 	<8 bit val>
//change sphero's accelerometer range, warning : may cause strange behaviors
{
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x14, 
			0x00, 
			0x02,
			&range, 
			waitConfirm, 
			resetTimer
		); 
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::roll(uint8_t speed, uint16_t heading,
		uint8_t state)
//02h 	30h 	<any> 	05h 	<val> 	<msb> 	<lsb> 	<val>
//roll the sphero with given direction and speed
/**state value is also provided. In the CES firmware, this was used to gate the 
 * control system to either obey the roll vector or ignore it and apply optimal 
 * braking to zero speed.  Please refer to Appendix C for detailed 
 * information.**/
{
	uint8_t msb = (uint8_t)((heading & 0xFF00) >> 8);
	uint8_t lsb = (uint8_t)(heading & 0x00FF);
	uint8_t data_payload[4];
	data_payload[0] = speed;
	data_payload[1] = msb;
	data_payload[2] = lsb;
	data_payload[3] = state;
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x02, 
			0x30, 
			0x00, 
			0x05,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
}

void Sphero::setInactivityTimeout(uint16_t timeout)
{
	if(timeout < 60)
	{
		timeout = 60;
	}
	timeout = htobe16(timeout);
	uint8_t* data = (uint8_t*) &timeout;
	ClientCommandPacket packet(
			0x00,
			0x25,
			0x00,
			0x03,
			data,
			waitConfirm,
			resetTimer
		);
	_btManager->send_data(packet.getSize(), packet.toByteArray());
}

void Sphero::sleep(uint16_t time, uint8_t macro,
		uint16_t orbbasic)
		
		/**00h 	22h 	<any> 	06h 	<16-bit val wakeup> 	<val macro> 	<16-bit val orbasic>

This command puts Sphero to sleep immediately. There are three optional parameters that program the robot for future actions:
name 	description
Wakeup 	The number of seconds for Sphero to sleep for and then automatically reawaken. Zero does not program a wakeup interval, so he sleeps forever. FFFFh attempts to put him into deep sleep (if supported in hardware) and returns an error if the hardware does not support it.
Macro 	If non-zero, Sphero will attempt to run this macro ID upon wakeup.
orbBasic 	If non-zero, Sphero will attempt to run an orbBasic program in Flash from this line number.**/
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
	ClientCommandPacket* packet = new ClientCommandPacket(
			0x00, 
			0x22, 
			0x00, 
			0x06,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager->send_data(packet->getSize(),packet->toByteArray());
	delete packet;
	
}

/*
//setRawMotorValue : not needed ?

void Sphero::setMotionTimeout(uint16_t time);

void Sphero::setPermOptFlags(uint32_t flags);

//getPermOptFlags : we'll see

void Sphero::setTmpOptFlags(uint32_t flags);

//getTmpOptFlags : we'll see

void Sphero::setDeviceMode(uint8_t value = 0);
//01h will set to user hack mode

//getDeviceMode

void Sphero::runMacro(uint8_t id);

//void saveMacro(Macro macro);
*/
