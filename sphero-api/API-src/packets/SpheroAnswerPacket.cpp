/*************************************************************************
                           SpheroAnswerPacket  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//------ Réalisation de la classe <SpheroAnswerPacket> (fichier SpheroAnswerPacket.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
#include <iostream>
#include <sys/select.h>
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
	//TODO: Implement
	fprintf(stderr, "Test : AnswerPacket\n");
	return false;
}




