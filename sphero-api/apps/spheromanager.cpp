/*************************************************************************
	SpheroManager  -  Sphero control application -- Sphero list manager
							 -------------------
	started                : 08/05/2015
*************************************************************************/

//-------------------------------------------------------- System includes
#include "../API-src/bluetooth/bluez_adaptor.h"
#include "../API-src/Sphero.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//--------------------------------------------------------- Local includes
#include "spheromanager.h"



//------------------------------------------------ Constructors/Destructor
/**
 * @brief SpheroManager : Constructor
 */
SpheroManager::SpheroManager():s(NULL), nbActif(0)
{}

SpheroManager::~SpheroManager()
{}


//--------------------------------------------------------- Public methods

/**
 * @brief listSpheros : Lists the currently connected Spheros
 */
void SpheroManager::listSpheros()
{
	for(int i = 0; i < spheroNames.size(); ++i)
	{
		cout << (spheroVec[i] == s) ? "*" : " ";
		cout << "[" << i << "] " << spheroNames[i] << endl;
	}
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
		cout << "Sphero : " << spheroNames[spheroIndex] << "has been removed." << endl;
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
