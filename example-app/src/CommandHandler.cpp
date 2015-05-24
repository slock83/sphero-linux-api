/*************************************************************************
	CommandHandler  -  Sphero control applicaiton -- command interpreter
							 -------------------
	started                : 08/05/2015
*************************************************************************/


//-------------------------------------------------------- System includes

#include <stddef.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <termios.h>

#include "sphero/bluetooth/bluez_adaptor.h"
#include "sphero/Sphero.hpp"
#include "sphero/packets/Constants.hpp"
//Test
#include <sphero/packets/answer/ColorStruct.hpp>

using namespace std;

//--------------------------------------------------------- Local includes
#include "CommandHandler.h"
#include "spheromanager.h"
#include "interactivecontroller.h"



/**/
static SpheroManager sm;
static InteractiveController ic;
/**/




void showHelp()
{
	cout << "=============================== HELP =================================" << endl;
	cout << "help -- Shows this" << endl;
	cout << "connect xx:xx:xx:xx:xx -- Connects the the Sphero at the given address" << endl;
	cout << endl;
	cout << "ping -- Does what it says" << endl;
	cout << "sleep <duration> -- Puts the sphero to sleep for the given duration" << endl;
	cout << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the Sphero color" << endl;
	cout << "backled <intensity> -- Changes the Sphero's back LED intensity" << endl;
	cout << "setIT <TO> -- Set inactivity timeout for the sphero" << endl;
	cout << "roll <speed> <angle> -- Moves the sphero" << endl;
	cout << "head <angle> -- Changes the heading angle(the new angle will be considered as 0 for roll)" << endl;
	cout << "collision -- Enable collision detection feature" << endl;
	cout << "coll -- Simulates a collision" << endl;
	cout << endl;
	cout << "list -- Shows the list of connected sphero" << endl;
	cout << "select <spheroId> -- Selects the Sphero to control" << endl;
	cout << "disconnect <spheroId> -- Disconnects the given Sphero" << endl;
	cout << endl;
	cout << "interactive -- switch to interactive mode (WIP)" << endl;
	cout << "======================================================================" << endl;
}

//------------------------------------------------- SpheroManager related

/**
 * @brief isConnected : Checks if a Sphero is connected
 */
static bool isConnected()
{
	if(sm.getSphero() == NULL)
	{
		cerr << "Please connect first" << endl;
		return false;
	}
	return true;
}


/**
 * @brief handleConnect : Handles the connexion command
 */
static void handleConnect(stringstream& css)
{
	string address;
	css >> address;
	sm.connectSphero(address);
}

/**
 * @brief handleSelect : Handles the selection command
 */
static void handleSelect(stringstream& css)
{
	size_t idx;
	css >> idx;
	sm.selectSphero(idx);
}

/**
 * @brief handleDisconnect : Handles the disconnect command
 */
static void handleDisconnect(stringstream& css)
{
	size_t idx;
	css >> idx;
	sm.disconnectSphero(idx);
}

//--------------------------------------------------------- Others

/**
 * @brief ping : Ping command...
 */
static void ping()
{
	if(!isConnected()) return;
	sm.getSphero()->ping();
}


/**
 * @brief handleCollision : Handles the collision detection activation
 */
static void handleCollision()
{
	if(!isConnected()) return;

	sm.getSphero()->enableCollisionDetection(80,0,80,0, 15);
}

/**
 * Simple test
 */
static void testGetColor()
{
	ColorStruct* ptr = sm.getSphero()->getColor();
	if(ptr != NULL)
	{
		fprintf(stdout, "SpheroColor (RVB) : %02x %02x %02x\n", ptr->red, ptr->green, ptr->blue);
	}
	else
	{
		fprintf(stderr, "Received nullptr\n");
	}
}



/**
 * @brief handleSleep : Handles the sleep command
 */
static void handleSleep(stringstream& css)
{
	if(!isConnected()) return;

	unsigned int time;
	css >> time;
	sm.getSphero()->sleep((uint16_t) time);
	sm.getSphero()->disconnect();
	sleep(time+3);
	sm.getSphero()->connect();
}

/**
 * @brief handleDirect : handles the roll command
 */
static void handleRoll(stringstream& css)
{
	if(!isConnected()) return;

	unsigned int speed;
	unsigned int angle;
	css >> speed >> angle;

	sm.getSphero()->roll((uint8_t) speed % 256, (uint16_t) angle % 0x10000, 1);

}


/**
 * @brief handleDirect : handles the roll command
 */
static void handleHead(stringstream& css)
{
	if(!isConnected()) return;

	unsigned int angle;
	css >> angle;

	sm.getSphero()->setHeading((uint16_t) angle % 360);

}
/**
 * @brief handleIT : Handles the set inactivity timeout command
 */
static void handleIT(stringstream& css)
{
	if(!isConnected()) return;

	uint16_t inactivityTO;
	css >> inactivityTO;

	sm.getSphero()->setInactivityTimeout(inactivityTO);

}

/**
 * @brief handleCc : Handles the changeColor command
 */
static void handleCc(stringstream& css)
{
	if(!isConnected()) return;

	unsigned int r, g, b;
	bool persist;

	css >> r >> g >> b >> persist;
#ifdef MAP
	std::cout << "[R, G, B] = " << r << " " << g << " " << b << std::endl;
#endif
	sm.getSphero()->setColor(
				(uint8_t) r%256,
				(uint8_t) g%256,
				(uint8_t) b%256,
				(persist==1)
				);
}

/**
 * @brief handleBackLED : Handles the back LED intensity
 */
static void handleBackLED(stringstream& css)
{
	if(!isConnected()) return;

	unsigned int i;

	css >> i;
#ifdef MAP
	std::cout << "i = " << i << std::endl;
#endif
	sm.getSphero()->setBackLedOutput((uint8_t) i%256);
}


void init()
{
}

/**
 * @brief handleCommand : Treats the command given in parameter
 * @param command : The command line
 * @return 0 for an exit command, 1 for a new connexion, -1 otherwise
 */
int handleCommand(const string& command)
{
	stringstream css(command);

	string cmd;
	css >> cmd;
	transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		//------------------------------ SpheroManager related
	if(cmd == "connect")
	{
		handleConnect(css);
		return 1;
	}
	else if(cmd == "select")
	{
		handleSelect(css);
	}
	else if(cmd == "list")
	{
		sm.listSpheros();
	}
	else if(cmd == "disconnect")
	{
		handleDisconnect(css);
	}
	else if(cmd == "coll")
	{
		if(isConnected()) {
			CollisionStruct coll;
			sm.getSphero()->reportCollision(&coll);
		}
	}
	else if(cmd == "interactive")
	{
		ic.startInteractiveMode(sm.getSphero());
	}
		//------------------------------ Others
	else if(cmd == "changecolor")
	{
		handleCc(css);
	}
	else if(cmd == "testcolor")
	{
		testGetColor();
	}
	else if(cmd == "backled")
	{
		handleBackLED(css);
	}
	else if(cmd == "roll")
	{
		handleRoll(css);
	}
	else if(cmd == "head")
	{
		handleHead(css);
	}
	else if(cmd == "collision")
	{
		handleCollision();
	}
	else if(cmd == "ping")
	{
		ping();
	}
	else if(cmd == "setit")
	{
		handleIT(css);
	}
	else if(cmd == "sleep")
	{
		handleSleep(css);
	}
	else if(cmd == "exit")
	{
			//To avoid memLeaks
		while(sm.getNbSpheros() > 0)
		{
			sm.disconnectSphero(0);
		}

		return 0;
	}
	else if(cmd == "read")
	{
		if(!isConnected()) cout << "please connect first" <<endl;

		else sm.getSphero()->setDataStreaming(1, 1, 0, 0, mask2::ODOMETER_X | mask2::ODOMETER_Y);
	}
	else if(cmd == "rst")
	{
		if(!isConnected()) cout << "please connect first" <<endl;

		else sm.getSphero()->configureLocator(0, 0, 0, 0);
	}
	else
		showHelp();

	return -1;
}
