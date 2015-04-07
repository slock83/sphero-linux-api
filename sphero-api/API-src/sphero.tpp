/*************************************************************************
 sphero  -  description
 -------------------
 début                : 7 avr. 2015
 copyright            : (C) 2015 par slock -- euhhhhh
 *************************************************************************/

//---------- Réalisation de la tâche <sphero> (fichier sphero.cpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel
#include <cstdint>

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
template<typename T>
sphero<T>::sphero(char const* const btaddr) {
	_btManager = new T();
	_btManager.connection(btaddr);
}

template<typename T>
sphero<T>::~sphero()
{
	//TODO : implement destructor
}

template<typename T>
void sphero<T>::setColor(uint8_t red, uint8_t green,
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
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x20, 
			0x00, 
			0x05,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::setBackLedOutput(uint8_t power)
//change the light intensity of the back led
//02h 	21h 	<any> 	02h 	<value>
{
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x21, 
			0x00, 
			0x02,
			&power, 
			waitConfirm, 
			resetTimer
		);
	_btManager.send_data(packet.getSize(),packet.toByteArray());

	delete packet;
}

template<typename T>
void sphero<T>::setHeading(uint16_t heading)
//Change the heading with and angle in ° (range from 0 to 359)
//02h 	01h 	<any> 	03h 	16-bit val
{
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x01, 
			0x00, 
			0x03,
			(uint8_t*) &heading, 
			waitConfirm, 
			resetTimer
		); //dirty, but should work. we'll have to try
	//Next time, feel free to test it yourself :-)
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::setStabilization(bool on)
//Enable or disable stabilization
//02h 	02h 	<any> 	02h 	<bool>
{
	uint8_t state;
	state = on ? 1 : 0;
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x02, 
			0x00, 
			0x02,
			&state, 
			waitConfirm, 
			resetTimer
		); 
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::setRotationRate(uint8_t angspeed)
//Change the rotation speed, as angspeed*0.784 degrees/sec
//Warning = high value may become really uncontrollable
//02h 	03h 	<any> 	02h 	<value>
{
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x03, 
			0x00, 
			0x02,
			&angspeed, 
			waitConfirm, 
			resetTimer
		); 
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::setSelfLevel(uint8_t options,
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
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x09, 
			0x00, 
			0x05,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}


//void sphero<T>::setDataStreaming(uint16_t N, uint16_t M,uint32_t MASK, uint8_t 
//pcnt, uint32_t MASK2 = 0); not used yet

template<typename T>
void sphero<T>::enableCollisionDetection(uint8_t Xt,
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
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x12, 
			0x00, 
			0x07,
			data_payload, 
			waitConfirm, 
			resetTimer
		);
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::disableCollisionDetection()
//pretty self-explanatory
{
	uint8_t data_payload[6];
	data_payload[0] = 0x00;
	data_payload[1] = 0;
	data_payload[2] = 0;
	data_payload[3] = 0;
	data_payload[4] = 0;
	data_payload[5] = 0;
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x12, 0x00, 0x07,
			data_payload, waitConfirm, resetTimer);
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::configureLocator(uint8_t flags, uint16_t X,
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
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x13, 0x00, 0x08,
			data_payload, waitConfirm, resetTimer);
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

//getLocator : will have to discuss this...
//getRGDLed : same

template<typename T>
void sphero<T>::setAccelerometerRange(uint8_t range)
//02h 	14h 	<any> 	02h 	<8 bit val>
//change sphero's accelerometer range, warning : may cause strange behaviors
{
	ClientCommandPacket packet = new ClientCommandPacket(
			0x02, 
			0x14, 
			0x00, 
			0x02,
			&range, 
			waitConfirm, 
			resetTimer
		); 
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

template<typename T>
void sphero<T>::roll(uint8_t speed, uint16_t heading,
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
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x09, 0x00, 0x05,
			data_payload, waitConfirm, resetTimer);
	_btManager.send_data(packet.getSize(),packet.toByteArray());
	delete packet;
}

/*
//setRawMotorValue : not needed ?

template<typename T>
void sphero<T>::setMotionTimeout(uint16_t time);

template<typename T>
void sphero<T>::setPermOptFlags(uint32_t flags);

//getPermOptFlags : we'll see

template<typename T>
void sphero<T>::setTmpOptFlags(uint32_t flags);

//getTmpOptFlags : we'll see

template<typename T>
void sphero<T>::setDeviceMode(uint8_t value = 0);
//01h will set to user hack mode

//getDeviceMode

template<typename T>
void sphero<T>::runMacro(uint8_t id);

template<typename T>
void sphero<T>::sleep(uint16_t time, uint8_t macro = 0,
		uint16_t orbbasic = 0);

//void saveMacro(Macro macro);
*/
