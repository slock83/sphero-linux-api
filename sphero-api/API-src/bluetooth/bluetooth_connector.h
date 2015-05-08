/*************************************************************************
	bluetooth_connector  -  Bluetooth connection utilities
                             -------------------
    début                : lun. 16 mars 2015
*************************************************************************/

#ifndef ( BLUETOOTHCONNECTOR_H )
#define BLUETOOTHCONNECTOR_H

//-------------------------------------------------------- System includes
#include <cstdio>


class bluetooth_connector 
{
	public:

		//--------------------------------------------- Operators overload
			//No sense
		bluetooth_connector & operator =
			( const bluetooth_connector & unbluetooth_connector ) = delete;


		//---------------------------------------- Constructors/Destructor
			//No sense
		bluetooth_connector (const bluetooth_connector & unbluetooth_connector) = delete;

		/**
		 * @brief bluetooth_connector : Constructor. Creates a new bluetoooth connector
		 */
		bluetooth_connector ()
		{}


		virtual ~bluetooth_connector ( )
		{}


		//------------------------------------------------- Public methods

		/**
		 * @brief connection : Establishes the connection
		 * @param address : The bluetooth address (format : 'XX:XX:XX:XX:XX:XX')
		 * @return A socket ID, or -1 if an error occurred
		 */
		virtual int connection(const char* address) = 0;

		/*
		 * Permet l'envoi d'un flux de données au destinataire
		virtual ssize_t send_data(size_t data_length, uint8_t const * data) = 0;
		 */

		/**
		 * @brief disconnect : Closes the actual connection
		 * @return The error code
		 */
		virtual int disconnect(void) = 0;

		/**
		 * @brief isConnected : Getter for the connection state
		 * @return true if the connector is connected
		 */
		virtual bool isConnected(void) = 0;
};

#endif // BLUETOOTHCONNECTOR_H

