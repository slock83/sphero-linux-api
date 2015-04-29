/*************************************************************************
                           bluez_adaptor  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//------ Réalisation de la classe <bluez_adaptor> (fichier bluez_adaptor.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sys/select.h>
#include <fcntl.h>

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
	if(_connected)
	{
		perror("déjà connecté, réinitialisation ...");
		disconnect();
		sleep(5);
	}


	bdaddr_t bt_address;

	//Conversion de l'adresse 
	if(str2ba(address, &bt_address))
	{
		perror("BT address conversion");
	}

	struct sockaddr_rc dest_addr;
	dest_addr.rc_bdaddr = bt_address;
	dest_addr.rc_family = AF_BLUETOOTH; 
	dest_addr.rc_channel = (uint8_t) 1;

	//Création du socket de communication
	_bt_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);	
	fcntl(_bt_socket, F_SETFL, O_NONBLOCK);

	if(connect(_bt_socket, (sockaddr*) &dest_addr, sizeof(dest_addr)) < 0)
	{
		perror("First attempt to connect");
	}
	pthread_create(&_listening_thread, NULL, monitorStream, &_bt_socket);
	
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

bool bluez_adaptor::isConnected()
{
	return _connected;
}

int bluez_adaptor::disconnect(void)
{
	_connected = false;	
	pthread_cancel(_listening_thread);
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
void* bluez_adaptor::monitorStream(void* arg)
{
	fd_set ensemble;
	ssize_t retour;
	int _bt_sock = *((int*) arg);
	uint8_t buf;
	ssize_t oldretour;
	bool continuer;
	for(;;)	
	{
		FD_ZERO(&ensemble);
		FD_SET(_bt_sock , &ensemble);
		while(
				select(_bt_sock + 1, 
					&ensemble,
					NULL, 
					NULL, 
					NULL
				) == -1 && errno == EINTR ){}
		//On ne fait pas de FD_ISSET car un seul fichier monitoré
				
		do{
			oldretour = retour;
			retour = recv(_bt_sock, &buf, sizeof(uint8_t), 0);
			continuer = true;

			if(retour > 0)
			{
				fprintf(stderr, "%02X ", buf); 
			}

			//Client disconnected
			else if(retour == -1 && oldretour == -1)
			{
				fprintf(stderr, "Déconnexion du client\n");
				pthread_exit(NULL);	
			}

			//Fin de lecture sur le flux
			else if(retour == -1 && errno == EAGAIN)
			{
				fprintf(stderr, "\n");
				continuer = false;
			}
			
			else
			{
				pthread_exit(NULL);
			}
		}while(continuer);
	}
}

