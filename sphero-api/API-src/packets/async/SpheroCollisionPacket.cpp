/*************************************************************************
   SpheroCollisionPacket  - Represents an asynchronous collision packet
                             -------------------
    début                : jeu. 07 mai 2015
*************************************************************************/

//-------------------------------------------------------- System includes
#ifdef MAP
	#include <iostream>
	using namespace std;
#endif
#include <sys/socket.h>


//--------------------------------------------------------- Local includes
#include "SpheroCollisionPacket.hpp"
#include "../Toolbox.hpp"


//-------------------------------------------------------------- Constants
static size_t const PACKET_SIZE = 19;


//------------------------------------------------ Constructors/Destructor

/**
 * @brief SpheroCollisionPacket : Constructor
 * @param sphero : The Sphero instance that sends the collision packet
 */
SpheroCollisionPacket::SpheroCollisionPacket(Sphero* sphero):
		SpheroAsyncPacket(sphero)
{}


SpheroCollisionPacket::~SpheroCollisionPacket ( )
{
#ifdef MAP
	std::cout << "<SpheroCollisionPacket> destructor called" << std::endl;
#endif
}


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
bool SpheroCollisionPacket::extractPacket(int fd,  Sphero* sphero, SpheroPacket** packet_ptr)
{
#ifdef MAP
	fprintf(stdout, "Receiving collision detection packet\n");
#endif

	uint8_t packet_data[PACKET_SIZE];
	if(recv(fd, &packet_data, sizeof(packet_data), 0) != sizeof(packet_data))
	{
		return false;
	}
	if(!Toolbox::checksum(packet_data+2, packet_data[18]))
	{
		return false;
	}	
	
	return false;
}

/**
 * @brief packetAction : Performs the action associated to the packet
 *			on the Sphero instance
 */
void SpheroCollisionPacket::packetAction()
{
	_sphero->reportCollision();
}
