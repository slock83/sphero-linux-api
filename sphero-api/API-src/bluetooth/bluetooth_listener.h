/*************************************************************************
	bluetooth_listener -
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

#ifndef ( BLUETOOTH_LISTENER_H )
#define BLUETOOTH_LISTENER_H

//-------------------------------------------------------- System includes
#include <cstdint>


class bluetooth_listener 
{
	public:
		//------------------------------------------------- Public methods

		/**
		 * @brief manage_data
		 * @param data_length
		 * @param data
		 */
		virtual void manage_data(size_t data_length, uint8_t* data) = 0;

		//--------------------------------------------- Operators overload
			//No sense
		bluetooth_listener & operator = ( const bluetooth_listener & unbluetooth_listener ) = delete;

		//---------------------------------------- Constructors/Destructor
			//No sense
		bluetooth_listener ( const bluetooth_listener & unbluetooth_listener ) = delete;

		virtual ~bluetooth_listener ( );
};

#endif // BLUETOOTH_LISTENER_H

