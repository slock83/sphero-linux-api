#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

#include "CommandHandler.h"
#include "ISphero.hpp"

using namespace std;

/**/
static Sphero *s = NULL;
/**/


static void showHelp()
{
	cout << "=============================== HELP =================================" << endl;
	cout << "help -- Shows this" << endl;
	cout << "connect xx:xx:xx:xx:xx -- Connects the the Sphero at the given address" << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the Sphero color" << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the Sphero color" << endl;
	cout << "direct <speed> <angle> -- Changes the Sphero color" << endl;
}

static void ping()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}
	s->ping();
}


static void handleConnect(stringstream& css)
{
	//void
	string address;
	css >> address;
	/*
	regex r("[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}");
	if(!regex_match(address, r))
	{
		cerr << "Usage: connect xx:xx:xx:xx:xx" << endl;
		return;
	}
	
	if(s != NULL)
		delete s;
	*/
	s = new Sphero(address.c_str());
}

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
	s->reconnect();
}

static void handleDirect(stringstream& css)
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
	std::cout << "[R, G, B] = " << r << " " <<
			g << " " << b << std::endl;
#endif
	s->setColor(
			(uint8_t) r%256, 
			(uint8_t) g%256, 
			(uint8_t) b%256, 
			(persist==1)
		);
}

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
		handleDirect(css);
	}
	else if(cmd == "ping")
	{
		ping();
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
