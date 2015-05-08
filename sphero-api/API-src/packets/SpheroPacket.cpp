/*************************************************************************
	SpheroPacket  -  Abstract class. Defines the behavior of
												packets received by Sphero
                             -------------------
    début                : mer. 06 mai 2015
*************************************************************************/


//-------------------------------------------------------- System includes
#include <iostream>
#include <limits>
#include <sys/socket.h>

//--------------------------------------------------------- Local includes
#include "SpheroPacket.hpp"
#include "SpheroAsyncPacket.hpp"
#include "SpheroAnswerPacket.hpp"

//-------------------------------------------------------- Class variables
extractorMap_t SpheroPacket::_extractorMap = {
	{ASYNC_FLAG, SpheroAsyncPacket::extractPacket},
	{ANSWER_FLAG, SpheroAnswerPacket::extractPacket}
};


//------------------------------------------------ Constructors/Destructor

/**
 * @brief SpheroPacket::SpheroPacket
 * @param sphero : The Sphero instance to which the packet is linked
 */
SpheroPacket::SpheroPacket(Sphero* sphero):_sphero(sphero)
{}


SpheroPacket::~SpheroPacket ( )
{}


//--------------------------------------------------------- Public methods

/**
 * @brief extractPacket : extracts informations from the file descriptor to build a well made packet
 * @param fd : The socket file descriptor
 * @param sphero : The Sphero sending the packet
 * @param packet_ptr : A pointer to a SpheroPacket pointer
 * @return true if the packet was successfully extracted from the socket, false otherwise
 *
 * Contract: the socket has to be in blocking read
 */
bool SpheroPacket::extractPacket(
		int fd,
		Sphero* sphero,
		SpheroPacket** packet_ptr)
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
