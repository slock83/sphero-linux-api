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

#include "../API-src/bluetooth/bluez_adaptor.h"
#include "../API-src/Sphero.hpp"

using namespace std;

//--------------------------------------------------------- Local includes
#include "CommandHandler.h"
#include "Keys.hpp"
#include "spheromanager.h"

#define _SPEED 128


/**/
static SpheroManager sm;
/**/

class BufferToggle
{
	private:
		struct termios t;
		struct termios o;

	public:

		/*
		 * Disables buffered input
		 */
		void off(void)
		{
			tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
			o = t;
			t.c_lflag &= ~ICANON; //disable canonical mmode
			t.c_lflag &= ~ECHO; //disable echoing
			t.c_lflag &= ~ISIG;
			t.c_cc[VMIN] = 0;
			t.c_cc[VTIME] = 0;
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings

		}

		/*
		 * Enables buffered input
		 * MUST be run AFTER off
		 */
		void on(void)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &o); //Apply the new settings
		}
};


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

/**
 * @brief interactiveMode : Activates the interactive Sphero directing mode
 */
static void interactiveMode()
{
	if(!isConnected()) return;
	cout << "welcome to interactive mode" <<endl;
	cout << "press q to quit" <<endl;
	cout << "arrow key to move" <<endl;
	cout << "r or t to reorient" <<endl;
	cout << "WARNING : early WIP !!!"<<endl;
	BufferToggle bt;
	bt.off();
	int input;
	int previousHeading = 0;
	unsigned int lastAng =0;
	timeval lastInput, now;
	double elapsedTime;

	// start timer
	gettimeofday(&lastInput, NULL);
	do
	{
	input = getchar();
	if(input == KEY_UP )
	{
		sm.getSphero()->roll((uint8_t)_SPEED % 256,(uint16_t) 0 % 0x10000,1);
		lastAng =0;
		gettimeofday(&lastInput, NULL);
	}
	else if(input == KEY_DOWN )
	{
		sm.getSphero()->roll((uint8_t)_SPEED % 256,(uint16_t) 180 % 0x10000,1);
		lastAng = 180;
		gettimeofday(&lastInput, NULL);
	}
	else if(input == KEY_RIGHT )
	{
		sm.getSphero()->roll((uint8_t)_SPEED % 256,(uint16_t) 90 % 0x10000,1);
		lastAng = 90;
		gettimeofday(&lastInput, NULL);
	}
	else if(input == KEY_LEFT )
	{
		sm.getSphero()->roll((uint8_t) _SPEED % 256, (uint16_t) 270 % 0x10000, 1);
		lastAng = 270;
		gettimeofday(&lastInput, NULL);
	}
	else if(input == KEY_R )
	{
		previousHeading+=2;
		if (previousHeading >=360) previousHeading = 0;
		sm.getSphero()->setHeading((uint16_t)previousHeading% 0x10000);
		gettimeofday(&lastInput, NULL);
	}
	else if(input == KEY_T )
	{
		previousHeading-=2;
		if (previousHeading <0) previousHeading = 359;
		sm.getSphero()->setHeading((uint16_t)previousHeading% 0x10000);
		gettimeofday(&lastInput, NULL);
	}
#ifdef MAP
	cout << "You pressed key ID: " << input << endl;
#endif
	gettimeofday(&now, NULL);
	elapsedTime = (now.tv_sec - lastInput.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (now.tv_usec - lastInput.tv_usec) / 1000.0;
	//cout << elapsedTime << endl;
	if(elapsedTime >= 120) sm.getSphero()->roll((uint8_t) 0 % 256, (uint16_t) lastAng % 0x10000, 1);
	usleep(8000);
	}while(input != KEY_Q);
	bt.on();
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

	sm.getSphero()->enableCollisionDetection(1,128,1,128, 15);
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
		interactiveMode();
	}
		//------------------------------ Others
	else if(cmd == "changecolor")
	{
		handleCc(css);
	}
	else if(cmd == "backled")
	{
		handleBackLED(css);
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
	else if(cmd == "sleep")
	{
		handleSleep(css);
	}
	else if(cmd == "exit")
			//To avoid memLeaks
		while(sm.getNbSpheros() > 0)
			sm.disconnectSphero(0);

		return 0;
	else
		showHelp();

	return -1;
}
