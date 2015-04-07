/*************************************************************************
 sphero  -  description
 -------------------
 début                : 7 avr. 2015
 copyright            : (C) 2015 par slock
 *************************************************************************/

//---------- Réalisation de la tâche <sphero> (fichier sphero.cpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel
#include "sphero.hpp"

#include <cstdint>

#include "ClientCommandPacket.hpp"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

void sphero<bluez_adaptor>::sendPack(ClientCommandPacket pack)
{
	//TODO : implement this
}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

/*
 * BT address (format : "XX:XX:XX:XX:XX:XX")
 */
sphero<bluez_adaptor>::sphero(char* btaddr)
{
	//TODO : implement constructor
}

virtual sphero<bluez_adaptor>::~sphero()
{
	//TODO : implement destructor
}

void sphero<bluetooth_connector>::setColor(uint8_t red, uint8_t green,
		uint8_t blue, bool persist = false)
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
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x20, 0x00, 0x05,
			data_payload, waitConfirm, resetTimer);
	sendPack(packet);
	delete packet;
}

void sphero<bluetooth_connector>::setBackLedOutput(uint8_t power)
//02h 	21h 	<any> 	02h 	<value>
{
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x21, 0x00, 0x02,
			power, waitConfirm, resetTimer);
	sendPack(packet);
	delete packet;
}

void sphero<bluetooth_connector>::setHeading(uint16_t heading)
//Change the heading with and angle in ° (range from 0 to 359)
//02h 	01h 	<any> 	03h 	16-bit val
{
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x01, 0x00, 0x03,
			*heading, waitConfirm, resetTimer); //dirty, but should work. we'll have to try
	sendPack(packet);
	delete packet;
}

void sphero<bluetooth_connector>::setStabilization(bool on)
//Enable or disable stabilization
//02h 	02h 	<any> 	02h 	<bool>
{
	uint8_t state;
	on ? state=1 : state=0;
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x02, 0x00, 0x02,
			*state, waitConfirm, resetTimer); //dirty, but should work. we'll have to try
	sendPack(packet);
	delete packet;
}

void sphero<bluetooth_connector>::setRotationRate(uint8_t angspeed)
//Change the rotation speed, as angspeed*0.784 degrees/sec
//Warning = high value may become really uncontrollable
//02h 	03h 	<any> 	02h 	<value>
{
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x03, 0x00, 0x02,
			*angspeed, waitConfirm, resetTimer); //dirty, but should work. we'll have to try
	sendPack(packet);
	delete packet;
}

void sphero<bluetooth_connector>::setSelfLevel(uint8_t options = 0,
		uint8_t angle_limit = 3, uint8_t timeout = 15, uint8_t trueTime = 30)
/**02h 	09h 	<any> 	05h 	<byte> 	<byte> 	<byte> 	<byte>

This command controls the self level routine. The self level routine attempts to achieve a horizontal orientation where pitch and roll angles are less than the provided Angle Limit. After both angle limits are satisfied, option bits control sleep, final angle (heading), and control system on/off. An asynchronous message is returned when the self level routine completes (only when started by API call). The required parameters are:
Name 	Value 	Description
Start/Stop Bit 0 0 aborts the routine if in progress. 1 starts the routine.
Final Angle Bit 1 0 just stops. 1 rotates to heading equal to beginning heading.
Sleep Bit 2 0 stays awake after leveling. 1 goes to sleep after leveling.
Control System 	Bit 3 0 leaves control system off. 1 leaves control system on (after leveling).

Angle Limit 	0 Use the default value
				1 to 90 Set the max angle for completion (in degrees)
Timeout 	0 Use the default value
			1 to 255 Set maximum seconds to run the routine
True Time 	0 Use the default value
			1 to 255 Set the required “test for levelness” time to 10*True Time (in milliseconds) **/
{
	uint8_t data_payload[4];
	data_payload[0] = options;
	data_payload[1] = angle_limit;
	data_payload[2] = timeout;
	data_payload[3] = trueTime;
	ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x09, 0x00, 0x05,
			data_payload, waitConfirm, resetTimer);
	sendPack(packet);
	delete packet;
}


//void sphero<bluetooth_connector>::setDataStreaming(uint16_t N, uint16_t M,uint32_t MASK, uint8_t pcnt, uint32_t MASK2 = 0); not used yet

void sphero<bluetooth_connector>::enableCollisionDetection(uint8_t Xt,
		uint8_t Xspd, uint8_t Yt, uint8_t Yspd, uint8_t Dead);

void sphero<bluetooth_connector>::disableCollisionDetection();

void sphero<bluetooth_connector>::configureLocator(uint8_t flags, uint16_t X,
		uint16_t Y, uint16_t yaw);

//getLocator : will have to discuss this...
//getRGDLed : same

void sphero<bluetooth_connector>::setAccelerometerRange(uint8_t range);

void sphero<bluetooth_connector>::roll(uint8_t speed, uint16_t heading,
		uint8_t state);

//setRawMotorValue : not needed ?

void sphero<bluetooth_connector>::setMotionTimeout(uint16_t time);

void sphero<bluetooth_connector>::setPermOptFlags(uint32_t flags);

//getPermOptFlags : we'll see

void sphero<bluetooth_connector>::setTmpOptFlags(uint32_t flags);

//getTmpOptFlags : we'll see

void sphero<bluetooth_connector>::setDeviceMode(uint8_t value = 0);
//01h will set to user hack mode

//getDeviceMode

void sphero<bluetooth_connector>::runMacro(uint8_t id);

void sphero<bluetooth_connector>::sleep(uint16_t time, uint8_t macro = 0,
		uint16_t orbbasic = 0);

//void saveMacro(Macro macro);
