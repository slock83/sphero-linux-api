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
#include <termios.h>
#include "../API-src/bluetooth/bluez_adaptor.h"
#include "../API-src/Sphero.hpp"
#include "Keys.hpp"

#include "spheromanager.h"

using namespace std;

/**/
static SpheroManager sm;
/**/

class BufferToggle
{
	private:
		struct termios t;

	public:

		/*
		 * Disables buffered input
		 */

		void off(void)
		{
			tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
			t.c_lflag &= ~ICANON; //disable canonical mmode
<<<<<<< HEAD
			t.c_lflag &= ~ECHO; //disable echoing
=======
			t.c_lflag &= ~ECHO;//disable echoing
>>>>>>> branch 'master' of https://github.com/slock83/sphero-linux-api.git
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
		}

<<<<<<< HEAD
		/*
		 * Enables buffered input
		 */
=======
>>>>>>> branch 'master' of https://github.com/slock83/sphero-linux-api.git

<<<<<<< HEAD
=======
		/*
		 * Enables buffered input
		 */

>>>>>>> branch 'master' of https://github.com/slock83/sphero-linux-api.git
		void on(void)
		{
			tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
			t.c_lflag |= ICANON;
			t.c_lflag |= ECHO;
			tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
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
	cout << "setIT <TO> -- Set inactivity timeout for the sphero" << endl;
	cout << "roll <speed> <angle> -- Moves the sphero" << endl;
	cout << "collision -- Enable collision detection feature" << endl;
	cout << endl;
	cout << "list -- Shows the list of connected sphero" << endl;
	cout << "select <spheroId> -- Selects the Sphero to control" << endl;
	cout << "disconnect <spheroId> -- Disconnects the given Sphero" << endl;
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
	uint16_t previousHeading = 0;
	do
	{
	input = getchar();
	if(input == KEY_UP )
	{
		sm.getSphero()->roll(128,0);
	}
	else if(input == KEY_DOWN )
	{
		sm.getSphero()->roll(128,180);
	}
	else if(input == KEY_RIGHT )
	{
		sm.getSphero()->roll(128, 90);
	}
	else if(input == KEY_LEFT )
	{
		sm.getSphero()->roll(128,270);
	}
	else if(input == KEY_R )
	{
		previousHeading++;
		sm.getSphero()->setHeading(previousHeading);
	}
	else if(input == KEY_T )
	{
		previousHeading--;
		sm.getSphero()->setHeading(previousHeading);
	}
#ifdef MAP
	cout << "You pressed key ID: " << input << endl;
#endif
	}while(input != KEY_Q);
	bt.on();
}

//--------------------------------------------------------- Others

/**
 * @brief ping : Ping command...
 */
static void ping()
{
	if(!isConnected())
	{
		cerr << "Please connect first" << endl;
		return;
	}
	sm.getSphero()->ping();
}


/**
 * @brief handleCollision : Handles the collision detection activation
 */
static void handleCollision()
{
	if(!isConnected())
	{
		cerr << "Please connect first" << endl;
		return;
	}

	sm.getSphero()->enableCollisionDetection(1,128,1,128, 15);
}


/**
 * @brief handleSleep : Handles the sleep command
 */
static void handleSleep(stringstream& css)
{
	if(!isConnected())
	{
		cerr << "Please connect first" << endl;
		return;
	}
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
	if(!isConnected())
	{
		cerr << "Please connect first" << endl;
		return;
	}

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
	if(!isConnected())
	{
		cerr << "Please connect first" << endl;
		return;
	}

	uint16_t inactivityTO;
	css >> inactivityTO;

	sm.getSphero()->setInactivityTimeout(inactivityTO);

}

/**
 * @brief handleCc : Handles the changeColor command
 */
static void handleCc(stringstream& css)
{
	if(!isConnected())
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
	sm.getSphero()->setColor(
				(uint8_t) r%256,
				(uint8_t) g%256,
				(uint8_t) b%256,
				(persist==1)
				);
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
		CollisionStruct coll;
		sm.getSphero()->reportCollision(&coll);
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
		return 0;
	else
		showHelp();

	return -1;
}
