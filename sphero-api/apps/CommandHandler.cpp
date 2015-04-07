#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

#include "CommandHandler.h"
#include "sphero.hpp"

using namespace std;

/**/
static sphero *s = NULL;
/**/


static void showHelp()
{
	cout << "=============================== HELP =================================" << endl;
	cout << "help -- Shows this" << endl;
	cout << "connect xx:xx:xx:xx:xx -- Connects the the sphero at the given address" << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the sphero color" << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the sphero color" << endl;
	cout << "direct <speed> <angle> -- Changes the sphero color" << endl;
}


static void handleConnect(stringstream& css)
{
	//void
	string address;
	css >> address;
	regex r("[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}");
	if(!regex_match(address, r))
	{
		cerr << "Usage: connect xx:xx:xx:xx:xx" << endl;
		return;
	}
	
	if(s != NULL)
		delete s;
	
	s = new sphero(address.c_str());
}

static void handleDirect(stringstream& css)
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}
	
	uint8_t speed;
	uint16_t angle;
	cin >> speed >> angle;
	s->setHeading(angle);
	s->setRotationRate(speed);
	
}

static void handleCc(stringstream& css)
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}
	uint8_t r, g, b;
	bool persist;
	
	css >> r >> g >> b >> persist;
	s->setColor(r, g, b);
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
	else if(cmd == "direct")
	{
		handleDirect(css);
	}
	else if(cmd == "exit")
		return 0;
	else
		showHelp();
	
	return -1;
}