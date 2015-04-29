/*************************************************************************
                           bluez_adaptor  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//---------- Interface de la classe <bluez_adaptor> (fichier bluez_adaptor.h) ------
#if ! defined ( BLUEZ_ADAPTOR_H )
#define BLUEZ_ADAPTOR_H

//-------------------------------------------------------------- Includes

#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "bluetooth_connector.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
//
//------------------------------------------------------------------------ 

class bluez_adaptor : public bluetooth_connector
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	
	/**
	 * Établie la connexion
	 */
	virtual int connection( const char* address);

	/**
	 * Permet l'envoi d'un flux de données au destinataire
	 */
	virtual ssize_t send_data(size_t data_length, uint8_t const * data);

	/**
	 * Ferme la connexion
	 */
	virtual int disconnect(void);

	virtual bool isConnected();

//------------------------------------------------- Surcharge d'opérateurs
	//N'a pas de sens
    bluez_adaptor & operator = ( const bluez_adaptor & unbluez_adaptor ) = delete;


//-------------------------------------------- Constructeurs - destructeur
    bluez_adaptor ( const bluez_adaptor & unbluez_adaptor ) = delete;

    bluez_adaptor ();

    virtual ~bluez_adaptor ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées
	static void* monitorStream(void* arg);
	int listen();

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	int _bt_socket;	
	bool _connected;
	pthread_t _listening_thread;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <bluez_adaptor>

#endif // BLUEZ_ADAPTOR_H

