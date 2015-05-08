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
#include <endian.h>


//--------------------------------------------------------- Local includes
#include "SpheroCollisionPacket.hpp"
#include "../Toolbox.hpp"
#include "CollisionStruct.hpp"


//-------------------------------------------------------------- Constants
static size_t const PACKET_SIZE = 19;


//------------------------------------------------ Constructors/Destructor

/**
 * @brief SpheroCollisionPacket : Constructor
 * @param sphero : The Sphero instance that sends the collision packet
 */
SpheroCollisionPacket::SpheroCollisionPacket(
		Sphero* sphero, 
		CollisionStruct* collisionInfos 
	):	SpheroAsyncPacket(sphero),
		_collisionInfos(collisionInfos)
{}


SpheroCollisionPacket::~SpheroCollisionPacket ( )
{
#ifdef MAP
	std::cout << "<SpheroCollisionPacket> destructor called" << std::endl;
#endif
	delete _collisionInfos;
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
	if(!packet_toolbox::checksum(packet_data+2, packet_data[18]))
	{
		return false;
	}	
	if(packet_data[0] != 0 || packet_data[1] != 0x10)
	{
		return false;
	}
	if(packet_data[5] > 3)
	{
		return false;
	}
	
	CollisionStruct* infos = new CollisionStruct();
	uint16_t* uint16_ptr = (uint16_t*) &packet_data[2];
	infos->impact_component_x = be16toh(*uint16_ptr++);	
	infos->impact_component_y = be16toh(*uint16_ptr++);	
	infos->impact_component_z = be16toh(*uint16_ptr);	
	
	infos->setAxis(packet_data[8]);

	uint16_ptr = (uint16_t*) &packet_data[9];
	infos->magnitude_component_x = be16toh(*uint16_ptr++); 
	infos->magnitude_component_y = be16toh(*uint16_ptr);

	infos->speed = packet_data[13];
	
	uint32_t* uint32_ptr = (uint32_t*) &packet_data[14];
	infos->timestamp = be32toh(*uint32_ptr);

	*packet_ptr = new SpheroCollisionPacket(sphero, infos);

	return true;
}

/**
 * @brief packetAction : Performs the action associated to the packet
 *			on the Sphero instance
 */
void SpheroCollisionPacket::packetAction()
{
	_sphero->reportCollision(_collisionInfos);
}
