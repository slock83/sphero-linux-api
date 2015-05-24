/*************************************************************************
                           SpheroAnswerPacket  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//------ Réalisation de la classe <SpheroAnswerPacket> (fichier SpheroAnswerPacket.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>

//--------------------------------------------------------- Local includes
#include "SpheroAnswerPacket.hpp"

//------------------------------------------------ Constructors/Destructor

/**
 * @brief SpheroAnswerPacket : Constructor
 * @param sphero : The Sphero instance that receives the answer packet
 */
SpheroAnswerPacket::SpheroAnswerPacket(Sphero* sphero) : SpheroPacket(sphero)	
{}


SpheroAnswerPacket::~SpheroAnswerPacket()
{}


//--------------------------------------------------------- Public methods

/**
 * @brief extractPacket : extracts the packet from a socket
 * @param fd : The socket file descriptor
 * @param sphero : The Sphero sending the packet
 * @param packet_ptr : A pointer to a SpheroPacket pointer
 * @return true if the packet was successfully extracted from the socket, false otherwise
 *
 * Contract: the socket has to be in blocking read
 */
bool SpheroAnswerPacket::extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr)
{
#ifdef MAP
	fprintf(stderr, "Answer packet reception\n\n");
#endif
	// À adapter
	uint8_t msgrsp;
	uint8_t seq;
	
	int rcvVal;
	rcvVal = recv(fd, &msgrsp, sizeof(msgrsp), 0);
	if(rcvVal != sizeof(msgrsp))
	{
		return false;
	}

	rcvVal = recv(fd, &seq, sizeof(seq), 0);
	if(rcvVal != sizeof(seq))
	{
		return false;
	}

#ifdef MAP
	fprintf(stdout, "msgrsp : %u ;\nseq : %u;\n", msgrsp, seq);
#endif
/*
	uint8_t idCode;
	int rcvVal = 0;

	rcvVal = recv(fd, &idCode, sizeof(idCode), MSG_PEEK);
	if(rcvVal != sizeof(idCode))
	{
		return false;
	}

	extractorMap_t::iterator mapIt = _extractorMap.find(idCode);
	if(mapIt != _extractorMap.end())
	{
		return mapIt->second(fd, sphero, packet_ptr);
	}
	recv(fd, &idCode, sizeof(idCode), 0);
*/
	return false;
	
}
