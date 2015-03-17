/*************************************************************************
                           bluez_adaptor  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//---------- Réalisation de la classe <bluez_adaptor> (fichier bluez_adaptor.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

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
	
	return 0;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur


bluez_adaptor::bluez_adaptor ():_bt_socket(0),_connecte(false)
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
} //----- Fin de ~bluez_adaptor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

