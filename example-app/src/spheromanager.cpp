/*************************************************************************
	SpheroManager  -  Sphero control application -- Sphero list manager
							 -------------------
	started                : 08/05/2015
*************************************************************************/

//-------------------------------------------------------- System includes
#include "sphero/bluetooth/bluez_adaptor.h"
#include "sphero/Sphero.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//--------------------------------------------------------- Local includes
#include "spheromanager.h"


//-------------------------------------------------------- Class variables
SpheroManager* SpheroManager::instance = new SpheroManager();


//------------------------------------------------ Constructors/Destructor
/**
 * @brief SpheroManager : Constructor
 */
SpheroManager::SpheroManager():s(NULL), nbActif(0)
{}

SpheroManager::~SpheroManager()
{}

SpheroManager* SpheroManager::getManager()
{
	return instance;
}


//--------------------------------------------------------- Public methods

/**
 * @brief listSpheros : Lists the currently connected Spheros
 */
vector<string> SpheroManager::listSpheros()
{
	return spheroNames;
}


/**
 * @brief getSelectedIndex : Returns the index of the currently selected Sphero
 * @return -1 if No Sphero is selected, the Sphero index in list otherwise
 */
unsigned int SpheroManager::getSelectedIndex()
{
	for(unsigned int i = 0; i < spheroVec.size(); ++i)
	{
		if(spheroVec[i] == s)
			return i;
	}
	return -1;
}


/**
 * @brief connectSphero : Connects a new Sphero into the application
 * @param address : The Sphero bluetooth address
 */
void SpheroManager::connectSphero(string address)
{
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

						sph->setColor(red, green, blue);
				});

	sph->onData([sph](){
		uint16_t var;

		if(sph->getDataBuffer()->waitForNext(dataTypes::ODOMETER_X, var, -1))
			cout << "posX:" << var << endl;

		if(sph->getDataBuffer()->waitForNext(dataTypes::ODOMETER_Y, var, -1))
			cout << "posY:" << var << endl;
	});

	if(sph->connect())
	{
		size_t idx = nbActif++;
		spheroVec.push_back(sph);
		spheroNames.push_back("Sphero"+idx);

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
}


/**
 * @brief selectSphero : Selects a Sphero to command
 * @param spheroIndex : The index of the Sphero to activate in the list
 */
void SpheroManager::selectSphero(unsigned int spheroIndex)
{
	if(nbActif > spheroIndex)
	{
		cout << "Active Sphero : "<< spheroIndex << endl;
		s = spheroVec[spheroIndex];
	}
	else
	{
		cout << "Error : invalid index" << endl;
	}
}


/**
 * @brief disconnectSphero : Disconnects and removes from the list a Sphero
 * @param spheroIndex : The index of the Sphero to disconnect in the list
 */
void SpheroManager::disconnectSphero(unsigned int spheroIndex)
{
	if(nbActif > spheroIndex)
	{
		if(s == spheroVec[spheroIndex])
		{
			s = NULL;
		}
		spheroVec[spheroIndex]->disconnect();
		delete spheroVec[spheroIndex];
		cout << "Sphero : " << spheroNames[spheroIndex] << " has been removed." << endl;
		nbActif--;
		spheroVec.erase(spheroVec.begin() + spheroIndex);
		spheroNames.erase(spheroNames.begin() + spheroIndex);
	}
	else
	{
		cout << "Error : invalid index" << endl;
	}
}


/**
 * @brief getSphero : Returns the currently selected Sphero
 * @return The selected Sphero
 */
Sphero* SpheroManager::getSphero()
{
	return s;
}


/**
 * @brief getNbSpheros : Returns the number of active Spheros
 */
int SpheroManager::getNbSpheros()
{
	return nbActif;
}
