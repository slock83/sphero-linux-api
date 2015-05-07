/*************************************************************************
                           SpheroAsyncPacket  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//------ Réalisation de la classe <SpheroAsyncPacket> (fichier SpheroAsyncPacket.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>

//------------------------------------------------------ Include personnel
#include "SpheroAsyncPacket.hpp"
#include "async/SpheroCollisionPacket.hpp"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe
extractorMap_t SpheroAsyncPacket::_extractorMap = {
	{COLLISION_DETECTED, SpheroCollisionPacket::extractPacket}
};
//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool SpheroAsyncPacket::extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr)
{
#ifdef MAP
	fprintf(stdout, "Réception d'un paquet asynchrone\n");
#endif
	uint8_t idCode;
	int rcvVal = 0;

	rcvVal = recv(fd, &idCode, sizeof(idCode), 0);
	if(rcvVal != sizeof(idCode))
	{
		return false;
	}

	extractorMap_t::iterator mapIt = _extractorMap.find(idCode);
	if(mapIt != _extractorMap.end())
	{
		return mapIt->second(fd, sphero, packet_ptr);
	}
	return false;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
SpheroAsyncPacket::SpheroAsyncPacket(Sphero* sphero) : SpheroPacket(sphero)
{

}

SpheroAsyncPacket::~SpheroAsyncPacket()
{

}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées


