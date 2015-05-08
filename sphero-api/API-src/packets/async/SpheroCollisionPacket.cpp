/*************************************************************************
    SpheroCollisionPacket
                             -------------------
    début                : jeu. 07 mai 2015
*************************************************************************/

//Réalisation de la classe <SpheroCollisionPacket> 
//(fichier SpheroCollisionPacket.cpp)

using namespace std;
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#ifdef MAP
	#include <iostream>
#endif
#include <sys/socket.h>
//------------------------------------------------------ Include personnel
#include "SpheroCollisionPacket.hpp"

//------------------------------------------------------------- Constantes
static size_t const PACKET_SIZE = 19;
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool SpheroCollisionPacket::extractPacket(
		int fd, 
		Sphero* sphero, 
		SpheroPacket** packet_ptr
	)
{
#ifdef MAP
	fprintf(stdout, "Réception d'un paquet de collision\n");
#endif
	uint8_t packet_data[PACKET_SIZE];
	if(recv(fd, &packet_data, sizeof(packet_data), 0) != sizeof(packet_data))
	{
		return false;
	}
	

	return false;
}

void SpheroCollisionPacket::packetAction()
{
	_sphero->reportCollision();
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SpheroCollisionPacket::SpheroCollisionPacket(Sphero* sphero):
	SpheroAsyncPacket(sphero)
{
	//Vide	
} 

SpheroCollisionPacket::~SpheroCollisionPacket ( )
// Algorithme :
//
{
#ifdef MAP
	std::cout << "Appel au destructeur de <SpheroCollisionPacket>" << std::endl;
#endif
} //----- Fin de ~SpheroCollisionPacket


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

