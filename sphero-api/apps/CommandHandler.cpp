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

using namespace std;

/**/
static Sphero* s;
static size_t nbActif = 0;
static vector<Sphero*> spheroVec;
/**/

void init()
{
	srand(time(NULL));
	spheroVec = vector<Sphero*>();
}//END init

void showHelp()
{
	cout << "=============================== HELP =================================" << endl;
	cout << "help -- Shows this" << endl;
	cout << "connect xx:xx:xx:xx:xx -- Connects the the Sphero at the given address" << endl;
	cout << "changecolor <red> <green> <blue> <persist> -- Changes the Sphero color" << endl;
	cout << "setIT <TO> -- set inactivity timeout for the sphero" << endl;
	cout << "roll <speed> <angle> -- moves the sphero" << endl;
	cout << "ping -- does what it says" << endl;
	cout << "sleep <duration> -- puts the sphero to sleep for the given duration" << endl;
	cout << "select <spheroid> -- Selects the sphero to control" << endl;
	cout << "collision -- enable collision detection feature" << endl;
    cout << "======================================================================" << endl;
}//END showHelp

static void handleConnect(stringstream& css)
{
	string address;
	css >> address;
	if(address.length() ==0)
	{
		ifstream myfile ("lastConnection");
		  if (myfile.is_open())
		  {
		    getline(myfile,address);
		    myfile.close();
		  }

		  else
			  {
			  cerr << "unable to load file"<<endl;
			  return;
			  }
	}

	Sphero* sph = new Sphero(address.c_str(), new bluez_adaptor());
	sph->onConnect([](){
				std::cout << "Here I come, honourable people !" << std::endl;
			});
	sph->onCollision([sph](CollisionStruct* infos){
					uint8_t red 	= (rand() + infos->timestamp) % 256;	
					uint8_t green 	= (rand() - (infos->timestamp / 13) ) % 256;
					uint8_t blue 	= (rand() + infos->impact_component_y) % 256;

					std::cout << "Collision : je change de couleur !"  << std::endl;

					sph->setColor(red, green, blue);
			});
	if(sph->connect())
	{
		size_t idx = nbActif++;
		spheroVec.push_back(sph);
		cout << "Sphero registered, ID : " << idx << endl;
		s = sph;
		ofstream myfile ("lastConnection", ios::out | ios::trunc);
		  if (myfile.is_open())
		  {
		    myfile <<address;
		    myfile.close();
		    cout << "Sphero address saved ! next time, just type \"connect\" :)"<< endl;
		  }
		  else cout << "Error : can't save the address :("<< endl;

	}
	else
	{
		delete sph;
		cout << "Connection error" << endl;
	}
}//END handleConnect

static void handleSelect(stringstream& css)
{
	size_t idx;
	css >> idx;
	if(nbActif > idx)
	{
		s = spheroVec[idx];
		cout << "Active sphero : "<< idx << endl;
	}

	else
	{
		cout << "ID not recognized" << endl;
	}
}//END handleSelect

static void ping()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}
	s->ping();
}//END ping

static void handleCollision()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return;
	}

	s->enableCollisionDetection(1,128,1,128, 15);
}//END handleCollision


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
}//END handleSleep

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
	
}//END handleDirect

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
	
}//END handleIT

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
}//END handleCC

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
	else if(cmd == "sleep")
	{
		handleSleep(css);
	}
	else if(cmd == "coll")
	{
		CollisionStruct coll;
		s->reportCollision(&coll);
	}
	else if(cmd == "exit")
		return 0;
	else
		showHelp();
	
	return -1;
}//END handleCommand
