/*************************************************************************
   SpheroStreamingPacket  - Represents an asynchronous collision packet
							 -------------------
	début                : jeu. 07 mai 2015
*************************************************************************/

//-------------------------------------------------------- System includes
//#ifdef MAP
	#include <iostream>
//#endif

#include <vector>
#include <sys/socket.h>
#include <endian.h>

using namespace std;

//--------------------------------------------------------- Local includes
#include "SpheroStreamingPacket.hpp"
#include "../../Sphero.hpp"
#include "../Toolbox.hpp"
#include "../Constants.hpp"
#include "DataBuffer.h"

//------------------------------------------------ Constructors/Destructor

/**
 * @brief SpheroStreamingPacket : Constructor
 * @param sphero : The Sphero instance that sends the collision packet
 */
SpheroStreamingPacket::SpheroStreamingPacket(
		Sphero* sphero):	SpheroAsyncPacket(sphero)
{}


SpheroStreamingPacket::~SpheroStreamingPacket ( )
{
#ifdef MAP
	std::cout << "<SpheroStreamingPacket> destructor called" << std::endl;
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
bool SpheroStreamingPacket::extractPacket(int fd,  Sphero* sphero, SpheroPacket** packet_ptr)
{
	uint8_t data;
	uint16_t len;

	sphero->requestLock();

	recv(fd, &data, sizeof(data), 0); // garbage?
	recv(fd, &data, sizeof(data), 0); // len MSB
		len = data << 8;

	recv(fd, &data, sizeof(data), 0); // len LSB
		len |= data;

	if(!sphero->checkValid(len))
	{
		sphero->requestLock(false);
		return false;
	}

	for(int i = 0; i < (len-1)/2; i++)
	{
		uint16_t value;
		recv(fd, &data, sizeof(data), 0);
		value = data << 8;
		recv(fd, &data, sizeof(data), 0);
		value |= data;

		sphero->getDataBuffer()->addValue(sphero->getTypesList()[i%sphero->getTypesList().size()], value);
	}

	sphero->requestLock(false);

	*packet_ptr = new SpheroStreamingPacket(sphero);
	return true;
}


/**
 * @brief packetAction : Performs the action associated to the packet
 *			on the Sphero instance
 */
void SpheroStreamingPacket::packetAction()
{
	_sphero->reportData();
}
