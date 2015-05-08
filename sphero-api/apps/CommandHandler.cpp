#include "CommandHandler.h"

#include <stddef.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../API-src/bluetooth/bluez_adaptor.h"
#include "../API-src/Sphero.hpp"

#include "spheromanager.h"

using namespace std;

/**/
static SpheroManager sm;
static Sphero* s;
static size_t nbActif = 0;
static vector<Sphero*> spheroVec;
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
	cout << "setIT <TO> -- Set inactivity timeout for the sphero" << endl;
	cout << "roll <speed> <angle> -- Moves the sphero" << endl;
	cout << "collision -- Enable collision detection feature" << endl;
	cout << endl;
	cout << "list -- Shows the list of connected sphero" << endl;
	cout << "select <spheroId> -- Selects the Sphero to control" << endl;
	cout << "disconnect <spheroId> -- Disconnects the given Sphero" << endl;
	cout << "======================================================================" << endl;
}

/**
 * @brief ping : Ping command...
 */
static void ping()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}
	s->ping();
}


/**
 * @brief handleCollision : Handles the collision detection activation
 */
static void handleCollision()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}

	s->enableCollisionDetection(1,128,1,128, 15);
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
	if(nbActif > idx)
	{
		s = spheroVec[idx];
		cout << "Active Sphero : "<< idx << endl;
	}

	else
	{
		cout << "Error : invalid index" << endl;
	}
}

/**
 * @brief handleSleep : Handles the sleep command
 */
static void handleSleep(stringstream& css)
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}
	unsigned int time;
	css >> time;
	s->sleep((uint16_t) time);
	s->disconnect();
	sleep(time+3);
	s->connect();
}

/**
 * @brief handleDirect : handles the roll command
 */
static void handleRoll(stringstream& css)
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}

	unsigned int speed;
	unsigned int angle;
	css >> speed >> angle;

	s->roll((uint8_t) speed % 256, (uint16_t) angle % 0x10000, 1);

}

/**
 * @brief handleIT : Handles the set inactivity timeout command
 */
static void handleIT(stringstream& css)
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}

	uint16_t inactivityTO;
	css >> inactivityTO;

	s->setInactivityTimeout(inactivityTO);

}

/**
 * @brief handleCc : Handles the changeColor command
 */
static void handleCc(stringstream& css)
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}

	unsigned int r, g, b;
	bool persist;

	css >> r >> g >> b >> persist;
#ifdef MAP
	std::cout << "[R, G, B] = " << r << " " << g << " " << b << std::endl;
#endif
	s->setColor(
				(uint8_t) r%256,
				(uint8_t) g%256,
				(uint8_t) b%256,
				(persist==1)
				);
}

void init()
{
	spheroVec = vector<Sphero*>();
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

	if(cmd == "connect")
	{
		handleConnect(css);
		return 1;
	}
	else if(cmd == "changecolor")
	{
		handleCc(css);
	}
	else if(cmd == "roll")
	{
		handleRoll(css);
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
	else if(cmd == "select")
	{
		handleSelect(css);
	}
	else if(cmd == "list")
	{
		//list();
	}
	else if(cmd == "disconnect")
	{
		//handleDisconnect(css);
	}
	else if(cmd == "sleep")
	{
		handleSleep(css);
	}
	else if(cmd == "exit")
		return 0;
	else
		showHelp();

	return -1;
}
