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
	sphero<bluez_adaptor>::sphero(char*  btaddr)
	{
		resetTimer = true;
		waitConfirm = false;
		//TODO : implement constructor
	}

	virtual sphero<bluez_adaptor>::~sphero ( )
	{
		//TODO : implement destructor
	}

	void sphero<bluetooth_connector>::setColor(uint8_t red, uint8_t green, uint8_t blue, bool persist = false)
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
		ClientCommandPacket packet = new ClientCommandPacket(0x02, 0x20, 0x00, 0x05, data_payload, waitConfirm, resetTimer);
		sendPack(packet);
	}

	void setBackLedOutput(uint8_t power);

	void setHeading(uint16_t heading);
	//Change the heading with and angle in ° (range from 0 to 359)

	void setStabilization(bool on = true);
	//Enable or disable stabilization

	void setRotationRate(uint8_t angspeed);
	//Change the rotation speed, as angspeed*0.784 degrees/sec
	//Warning = high value may become really uncontrollable

	void setSelfLevel(uint8_t options = 0, uint8_t angle_limit = 3, uint8_t timeout = 15, uint8_t trueTime = 30);

	void setDataStreaming(uint16_t N, uint16_t M, uint32_t MASK, uint8_t pcnt, uint32_t MASK2 = 0);

	void enableCollisionDetection(uint8_t Xt, uint8_t Xspd, uint8_t Yt, uint8_t Yspd, uint8_t Dead);

	void disableCollisionDetection();

	void configureLocator(uint8_t flags, uint16_t X, uint16_t Y, uint16_t yaw);

	//getLocator : will have to discuss this...
	//getRGDLed : same

	void setAccelerometerRange(uint8_t range);

	void roll(uint8_t speed, uint16_t heading, uint8_t state);

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
