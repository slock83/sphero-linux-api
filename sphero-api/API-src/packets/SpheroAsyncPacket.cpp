/*************************************************************************
                           SpheroAsyncPacket  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/


//-------------------------------------------------------- Include système
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>

//------------------------------------------------------ Include personnel
#include "SpheroAsyncPacket.hpp"
#include "async/SpheroCollisionPacket.hpp"

//---------------------------------------------------- Variables de classe
extractorMap_t SpheroAsyncPacket::_extractorMap = {
	{COLLISION_DETECTED, SpheroCollisionPacket::extractPacket}
};

//------------------------------------------------ Constructors/Destructor
SpheroAsyncPacket::SpheroAsyncPacket(Sphero* sphero) : SpheroPacket(sphero)
{}

SpheroAsyncPacket::~SpheroAsyncPacket()
{}


//--------------------------------------------------------- Public methods

/**
 * @brief extractPacket : extracts the packet from a socket
 * @param fd : The socket file descriptor
 * @param sphero : The Sphero sending the packet
 * @param packet_ptr : A pointer to a SpheroPacket pointer
 * @return true if the packet was successfully extracted from the socket, false otherwise
 */
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



