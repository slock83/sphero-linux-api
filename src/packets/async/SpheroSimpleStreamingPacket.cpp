/*************************************************************************
   SpheroSimpleStreamingPacket  - Represents an asynchronous collision packet
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
#include "SpheroSimpleStreamingPacket.hpp"
#include "../../Sphero.hpp"
#include "../Toolbox.hpp"
#include "../Constants.hpp"
#include "DataBuffer.h"

#include "../ChecksumComputer.hpp"

//------------------------------------------------ Constants
static size_t const PACKET_SIZE = 11;

//------------------------------------------------ Constructors/Destructor

/**
 * @brief SpheroSimpleStreamingPacket : Constructor
 * @param sphero : The Sphero instance that sends the collision packet
 */
SpheroSimpleStreamingPacket::SpheroSimpleStreamingPacket(
		Sphero* sphero,
		int16_t x,
		int16_t y,
		int16_t speedX,
		int16_t speedY
		):	SpheroAsyncPacket(sphero), _x(x), _y(y), _speedX(speedX), _speedY(speedY)
{}


SpheroSimpleStreamingPacket::~SpheroSimpleStreamingPacket ( )
{
#ifdef MAP
	std::cout << "<SpheroSimpleStreamingPacket> destructor called" << std::endl;
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
bool SpheroSimpleStreamingPacket::extractPacket(int fd,  Sphero* sphero, SpheroPacket**)
{
	uint8_t buf;
	uint8_t rawdata[PACKET_SIZE];
	int16_t x,y,speedX,speedY;

	ChecksumComputer cc;
#ifdef MAP
	std::cerr << "Creation d'un simplestreapacket" << std::endl;
#endif

	if(recv(fd, &buf, sizeof(buf), 0) != sizeof(buf))
	{
		return false;	
	}

	cc.addField(buf);

	if(recv(fd, rawdata, sizeof(rawdata), 0) != sizeof(rawdata))
	{
		return false;	
	}

	cc.addField(rawdata, PACKET_SIZE - 1);

	if(cc() !=  rawdata[10])
	{
#ifdef MAP
		std::cerr << "Erreur checksum" << std::endl;
#endif
		return false;
	}
	
	x = (int16_t) be16toh(*((uint16_t*)(&(rawdata[2]))));
	y = (int16_t) be16toh(*((uint16_t*)(&(rawdata[4]))));
	speedX = (int16_t) be16toh(*((uint16_t*)(&(rawdata[6]))));
	speedY = (int16_t) be16toh(*((uint16_t*)(&(rawdata[8]))));
	sphero->setX(x);
	sphero->setY(y);
	sphero->setSpeedX(speedX);
	sphero->setSpeedY(speedY);

	return false;
}


/**
 * @brief packetAction : Performs the action associated to the packet
 *			on the Sphero instance
 */
void SpheroSimpleStreamingPacket::packetAction()
{
	_sphero->setX(_x);
	_sphero->setY(_y);
	_sphero->setSpeedX(_speedX);
	_sphero->setSpeedY(_speedY);	
}

