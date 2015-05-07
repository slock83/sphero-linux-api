/*************************************************************************
    SpheroPacket  -  description
                             -------------------
    début                : mer. 06 mai 2015
*************************************************************************/

//-- Réalisation de la classe <SpheroPacket> (fichier SpheroPacket.cpp) --
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <limits>
#include <sys/socket.h>

//------------------------------------------------------ Include personnel
#include "SpheroPacket.hpp"
#include "SpheroAsyncPacket.hpp"
#include "SpheroAnswerPacket.hpp"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe
extractorMap_t SpheroPacket::_extractorMap = {
	{ASYNC_FLAG, SpheroAsyncPacket::extractPacket},
	{ANSWER_FLAG, SpheroAnswerPacket::extractPacket}
};

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
//Contrat : le socket doit être en lecture bloquante
bool SpheroPacket::extractPacket(
		int fd,
		Sphero* sphero,
		SpheroPacket** packet_ptr
	)
{
	uint8_t buf;
	int rcvVal = 0;

	for(;;)
	{
		rcvVal = recv(fd, &buf, sizeof(buf), 0);

		//Socket is closed
		if(rcvVal != sizeof(buf))
		{
			return false;
		}
		if(buf == START_OF_PACKET_FLAG)
		{
			if(recv(fd, &buf, sizeof(buf), 0) != sizeof(buf))
			{
				return false;
			}
			
			extractorMap_t::iterator mapIt = _extractorMap.find(buf);
			if(mapIt == _extractorMap.end())
			{
				return false;
			}
			else
			{
				return mapIt->second(fd, sphero, packet_ptr);
			}
		}
	}

}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

SpheroPacket::SpheroPacket(Sphero* sphero):_sphero(sphero)
{
}


SpheroPacket::~SpheroPacket ( )
{
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

