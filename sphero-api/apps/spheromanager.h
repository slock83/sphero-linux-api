/*************************************************************************
	SpheroManager  -  Sphero control application -- Sphero list manager
							 -------------------
	started                : 08/05/2015
*************************************************************************/

#ifndef SPHEROMANAGER_H
#define SPHEROMANAGER_H

//-------------------------------------------------------- System includes
#include <string>
#include <vector>
#include "../API-src/Sphero.hpp"

//------------------------------------------------------- Class definition
class SpheroManager
{
	public:
		//--------------------------------------- Constructors/Destructor
		/**
		 * @brief SpheroManager : Constructor
		 */
		SpheroManager();

		virtual ~SpheroManager();


		//------------------------------------------------ Public methods

		/**
		 * @brief listSpheros : Lists the currently connected Spheros
		 */
		void listSpheros();


		/**
		 * @brief connectSphero : Connects a new Sphero into the application
		 * @param address : The Sphero bluetooth address
		 */
		void connectSphero(string address);


		/**
		 * @brief selectSphero : Selects a Sphero to command
		 * @param spheroIndex : The index of the Sphero to activate in the list
		 */
		void selectSphero(unsigned int spheroIndex);


		/**
		 * @brief disconnectSphero : Disconnects and removes from the list a Sphero
		 * @param spheroIndex : The index of the Sphero to disconnect in the list
		 */
		void disconnectSphero(unsigned int spheroIndex);


		/**
		 * @brief getSphero : Returns the currently selected Sphero
		 * @return The selected Sphero
		 */
		Sphero* getSphero();


		/**
		 * @brief getNbSpheros : Returns the number of active Spheros
		 */
		int getNbSpheros();

	private:
		Sphero* s;
		size_t nbActif;
		vector<Sphero*> spheroVec;
		vector<string> spheroNames;
};

#endif // SPHEROMANAGER_H
