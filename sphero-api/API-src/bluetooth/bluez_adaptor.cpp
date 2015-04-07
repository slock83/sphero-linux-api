/*************************************************************************
                           bluez_adaptor  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//---------- Réalisation de la classe <bluez_adaptor> (fichier bluez_adaptor.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;
//------------------------------------------------------ Include personnel
#include "bluez_adaptor.h"


//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
int bluez_adaptor::connection(const char* address)
{
	bdaddr_t bt_address;

	//Conversion de l'adresse 
	if(!str2ba(address, &bt_address))
	{
		perror("BT address conversion");
	}

	struct sockaddr_rc dest_addr;
	dest_addr.rc_bdaddr = bt_address;
	dest_addr.rc_family = AF_BLUETOOTH; 
	dest_addr.rc_channel = (uint8_t) 1;

	//Création du socket de communication
	_bt_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);	

	if(connect(_bt_socket, (sockaddr*) &dest_addr, sizeof(dest_addr)) < 0)
	{
		perror("First attempt to connect");
	}
	
	_connected = true;
	return 0;
}

ssize_t bluez_adaptor::send_data(size_t data_length, uint8_t const * data)
{
	ssize_t retour;
	if((retour = send(_bt_socket, (char const *) data, data_length, MSG_NOSIGNAL)) == -1)
	{
		perror("Connexion perdue");
		disconnect();
	}
	return retour;
}

int bluez_adaptor::disconnect(void)
{
	_connected = false;	
	return close(_bt_socket);
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur


bluez_adaptor::bluez_adaptor ():
	bluetooth_connector(),
	_bt_socket(0),
	_connected(false)
{
#ifdef MAP
    cout << "Appel au constructeur de <bluez_adaptor>" << endl;
#endif
} //----- Fin de bluez_adaptor


bluez_adaptor::~bluez_adaptor ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <bluez_adaptor>" << endl;
#endif
	if(_connected)
	{
		disconnect();
	}
} //----- Fin de ~bluez_adaptor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
