#include <algorithm>
#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <vector>

#include "CommandHandler.h"
#include "Sphero.hpp"
#include "bluetooth/bluez_adaptor.h"

using namespace std;

/**/
static Sphero* s;
static size_t nbActif = 0;
static vector<Sphero*> spheroVec;
/**/


static void showHelp()
{
	cout << "=============================== HELP =================================" << endl;
	cout << "help -- Shows this" << endl;
	cout << "connect xx:xx:xx:xx:xx -- Connects the the Sphero at the given address" << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the Sphero color" << endl;
	cout << "setIT <TO> -- set inactivity timeout for the sphero" << endl;
	cout << "roll <speed> <angle> -- moves the sphero" << endl;
	cout << "ping -- does what it says" << endl;
	cout << "sleep <duration> -- puts the sphero to sleep for the given duration" << endl;
	cout << "select <spheroid> -- Sélectionne le sphéro à controller" << endl;
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

	Sphero* sph = new Sphero(address.c_str(), new bluez_adaptor());
	if(sph->connect())
	{
		size_t idx = nbActif++;
		spheroVec.push_back(sph);
		cout << "Sphero enregistré : identifiant " << idx << endl;
		s = sph;
	}
	else
	{
		delete sph;
		cout << "Erreur de connexion" << endl;
	}
}

static void handleSelect(stringstream& css)
{
	size_t idx;
	css >> idx;
	if(nbActif > idx)
	{
		s = spheroVec[idx];
		cout << "Sphero actif : "<< idx << endl;
	}

	else
	{
		cout << "Erreur d'indice" << endl;
	}
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
	s->connect();
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

void init()
{
	spheroVec = vector<Sphero*>();
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
	else if(cmd == "setit")
	{
		handleIT(css);
	}
	else if(cmd == "select")
	{
		handleSelect(css);
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
