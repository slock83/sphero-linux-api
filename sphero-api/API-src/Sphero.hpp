/************************************************************************
	Sphero  -  Wrapper implementing all sphero-linked features
								(like packet creation, emissionreception)
                             -------------------
	started                : 16/03/2015
 *************************************************************************/

#if ! defined ( SPHERO_HPP )
#define SPHERO_HPP

//--------------------------------------------------------- System includes
#include <pthread.h>
#include <cstdint>
#include <string>
#include <list>
#include <functional>

//---------------------------------------------------------- Local includes
#include "bluetooth/bluetooth_connector.h"
#include "packets/ClientCommandPacket.hpp"

//--------------------------------------------------------------- Constants

#define ABORT_ROUTINE 0x00
#define START_ROUTINE 0x01
#define CHECK_ANGLE 0x02
#define SLEEP_AFTER_FINISH 0x04
#define KEEP_CONTROL_SYSTEM 0x08


#define ACC_2G 0x00
#define ACC_4G 0x01
#define ACC_8G 0x02
#define ACC16G 0x03

//------------------------------------------------------------------- Types
class ClientCommandPacket;
class sphero_listener;

typedef int16_t spherocoord_t;

	/** Callback functions signatures definition */
typedef std::function<void(void)> callback_connect_t;
typedef std::function<void(void)> callback_disconnect_t;
typedef std::function
	<void(spherocoord_t, spherocoord_t)> callback_collision_t;


//-------------------------------------------------------- Class definition

class Sphero 
{
	public:


		//------------------------------------------------------- Operators
			//No sense
		Sphero & operator=(const Sphero&) = delete;

		//----------------------------------------- Constructors/Destructor
			//No sense
		Sphero (const Sphero&) = delete;

		/**
		 * @param btaddr : Device address (format : "XX:XX:XX:XX:XX:XX")
		 * @param btcon : A pointer to the bluetooth connector
		 */
		Sphero(char const * const btaddr, bluetooth_connector* btcon);

		virtual ~Sphero();

		//-------------------------------------------------- Public methods

		/**
		 * @brief connect : Initializes the bluetooth connection to the sphero instance
		 * @return true if the connection was successful, false otherwise
		 */
		bool connect();


		/**
		 * @brief disconnect : Disconnects the current Sphero
		 */
		void disconnect();


		/**
		 * @brief sendPacket : Send the specified packet to the Sphero
		 * @param packet : The packet to send to the Sphero
		 */
		void sendPacket(ClientCommandPacket& packet);


		/**
		 * @brief ping : Creates a ping request to the Sphero
		 */
		void ping();


		/**
		 * @brief setColor : Changes the Sphero light color
		 * @param red : level of red (between 0x00 and 0xFF)
		 * @param green : level of green (between 0x00 and 0xFF)
		 * @param blue : level of blue (between 0x00 and 0xFF)
		 * @param persist : true if you want the color to be defined as user color
		 */
		void setColor(uint8_t red, uint8_t green, uint8_t blue, bool persist = false);


		/**
		 * @brief setBackLedOutput : Lights the back led(used to calibrate the spero direction) with the given power
		 * @param power : The power the LED will receive
		 */
		void setBackLedOutput(uint8_t power);


		/**
		 * @brief setHeading : Change the heading angle
		 * @param heading : the new angle, in ° (range from 0 to 359)
		 */
		void setHeading(uint16_t heading);


		/**
		 * @brief setStabilization : Enable or disable stabilization
		 * @param on : enables if true, disables otherwise
		 */
		void setStabilization(bool on = true);


		/**
		 * @brief setRotationRate : Change the rotation speed
		 * @param angspeed : The new rotation speed (new speed will be angspeed*0.784 degrees/sec)
		 *		Warning :=: high value may become really uncontrollable
		 */
		void setRotationRate(uint8_t angspeed = 0xc8);


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
		void setSelfLevel(
				uint8_t options = 0, 
				uint8_t angle_limit = 3, 
				uint8_t timeout = 15, 
				uint8_t trueTime = 30
			);


		//void setDataStreaming(uint16_t N, uint16_t M, uint32_t MASK, uint8_t pcnt, uint32_t MASK2 = 0);


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
		void enableCollisionDetection(uint8_t Xt, uint8_t Xspd, uint8_t Yt, uint8_t Yspd, uint8_t Dead);


		/**
		 * @brief disableCollisionDetection : Disables the onBoard collision detector
		 */
		void disableCollisionDetection();

		/**
		 * @brief isConnected : Checks the Sphero's connection state
		 * @return true if it is connected.
		 */
		bool isConnected();

		/**
		 * @brief configureLocator : Configure sphero's internal location calculation unit offsets
		 * @param flags
		 * @param X
		 * @param Y
		 * @param yaw
		 */
		void configureLocator(uint8_t flags, uint16_t X, uint16_t Y, uint16_t yaw);


		//getLocator : will have to discuss this...
		//getRGDLed : same

		/**
		 * @brief setAccelerometerRange : change sphero's accelerometer range, warning : may cause strange behaviors
		 * @param range : The accelerometer range. Use one (and only one!) of the next flags to set the right range
		 *					Any other value will have indeterminate consequences for driving and collision detection
		 *				ACC_2G : ±2Gs
		 *				ACC_4G : ±4Gs
		 *				ACC_8G : ±8Gs (default)
		 *				ACC_16G : ±16Gs
		 */
		void setAccelerometerRange(uint8_t range = 0x02);

		/**
		 * @brief roll : Defines a new heading angle and a new rotation speed
		 * @param speed : The new rotation speed (new speed will be speed*0.784 degrees/sec)
		 * @param heading : the new angle, in ° (range from 0 to 359)
		 * @param state : In the CES firmware, this was used to gate the
		 *			control system to either obey the roll vector or ignore it and apply optimal
		 *			braking to zero speed
		 */
		void roll(uint8_t speed, uint16_t heading, uint8_t state = 0);


		//setRawMotorValue : not needed ?


		void setMotionTimeout(uint16_t time);


		void setPermOptFlags(uint32_t flags);


		//getPermOptFlags : we'll see


		void setTmpOptFlags(uint32_t flags);


		//getTmpOptFlags : we'll see


		void setDeviceMode(uint8_t value = 0);
		//01h will set to user hack mode


		//getDeviceMode


		void runMacro(uint8_t id);


		//void saveMacro(Macro macro);


		void sleep(uint16_t time, uint8_t macro = 0,uint16_t orbbasic = 0);


		void setInactivityTimeout(uint16_t timeout);
		

		void reportCollision();


		//------------ Evenements ------------//
		// type(types) : signature attendue pour le callback

		// void(void)
		void onConnect(callback_connect_t callback);

		// void(void)
		void onDisconnect(callback_disconnect_t callback);

		// void(spherocoord_t, spherocoord_t)
		void onCollision(callback_collision_t callback);

		//------------------------------------------------------------------ PRIVE

	protected:
		//---------- ------------------------------------------- Méthodes protégées
		static void* monitorStream(void* sphero_ptr);

		void handleOnConnect();
		void handleOnDisonnect();
		void handleOnCollision(spherocoord_t x, spherocoord_t y);

	private:
		//------------------------------------------------------- Attributs privés

		static const size_t MAX_CONNECT_ATTEMPT = 5;
		bool _connected;

		bluetooth_connector* _bt_adapter;
		
		spherocoord_t _position_x;
		spherocoord_t _position_y;

		/*
		* X accelerometer
		*/
		spherocoord_t accelerometer_x;

		/*
		* Y accelerometer
		*/
		spherocoord_t accelerometer_y;

		/*
		* Z accelerometer
		*/
		spherocoord_t accelerometer_z;

		//To be continued

		bool resetTimer = true;
		bool waitConfirm = false;

		int _bt_socket;
		pthread_t monitor;

		const std::string _address;

		// Liste de callback pour chaque événement

		std::list<callback_connect_t> _callback_connect_list;
		std::list<callback_disconnect_t> _callback_disconnect_list;
		std::list<callback_collision_t> _callback_collision_list;
};

#endif // SPHERO_HPP
