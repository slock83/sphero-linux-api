/*************************************************************************
	bluez_adaptor  -  Bluez stack adaptor for Sphero
                             -------------------
	started                : 17/03/2015
*************************************************************************/

#ifndef BLUEZ_ADAPTOR_H
#define BLUEZ_ADAPTOR_H

//------------------------------------------------------- System includes
#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

//-------------------------------------------------------- Local includes
#include "bluetooth_connector.h"


//------------------------------------------------------- Class definition
class bluez_adaptor : public bluetooth_connector
{
	public:

		//-------------------------------------------- Operators overload
			//No sense
		bluez_adaptor & operator=(const bluez_adaptor & unbluez_adaptor) = delete;


		//--------------------------------------- Constructors/Destructor
			//No sense
		bluez_adaptor(const bluez_adaptor & unbluez_adaptor) = delete;

		/**
		 * @brief bluez_adaptor : Constructor
		 */
		bluez_adaptor();

		virtual ~bluez_adaptor ( );

		//------------------------------------------------ Public methods

		/**
		 * @brief connection : Establishes the connection
		 * @param address : Thedevice address (format : 'XX:XX:XX:XX:XX')
		 * @return The socket ID, or -1 if an error occurred
		 */
		virtual int connection( const char* address);

		/**
		 * @brief disconnect : Closes the connections
		 * @return An error code
		 */
		virtual int disconnect(void);

		/**
		 * @brief isConnected : Checks the connection status
		 * @return true if the connection is currently established
		 */
		virtual bool isConnected();

	private:

			/* The socket associated to the connector */
		int _bt_socket;
			/* The connection state */
		bool _connected;
};

#endif // BLUEZ_ADAPTOR_H
