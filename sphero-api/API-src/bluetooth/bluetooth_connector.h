/*************************************************************************
                           bluetooth_connector  -  description
                             -------------------
    début                : lun. 16 mars 2015
*************************************************************************/

//---------- Interface de la classe <bluetooth_connector> (fichier bluetooth_connector.h) ------
#if ! defined ( BLUETOOTHCONNECTOR_H )
#define BLUETOOTHCONNECTOR_H

//--------------------------------------------------- Interfaces utilisées
#include "bluetooth_listener.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 

class bluetooth_connector 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	/*
	 * Établie la connexion
	 * address <-> BT Address : 'XX:XX:XX:XX:XX:XX'
	 */
	virtual int connection(const char* address) = 0;

	/*
	 * Permet l'envoi d'un flux de données au destinataire
	 */
	virtual ssize_t send_data(size_t data_length, uint8_t const * data) = 0;

	/*
	 * Ferme la connexion
	 */
	virtual int disconnect(void) = 0;

	/*
	 * Informe de l'état de la connexion
	 */
	virtual bool isConnected(void) = 0;
	
	/**
	 * Met à jour le listener
	 */
	void set_listener(bluetooth_listener* bluetooth_listener)
	{
		_bluetooth_listener = bluetooth_listener;
	}

//------------------------------------------------- Surcharge d'opérateurs
	//N'a pas de sens
    bluetooth_connector & operator = 
		( const bluetooth_connector & unbluetooth_connector ) = delete;

//-------------------------------------------- Constructeurs - destructeur
	//N'a pas de sens
    bluetooth_connector (const bluetooth_connector & unbluetooth_connector) = delete;

	bluetooth_connector ():
		_bluetooth_listener(NULL)
	{}
	
    virtual ~bluetooth_connector ( )
	{

	}

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	/*
	 * Is keeped up to date when data is received
	 */
	bluetooth_listener const * _bluetooth_listener;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <bluetooth_connector>

#endif // BLUETOOTHCONNECTOR_H

