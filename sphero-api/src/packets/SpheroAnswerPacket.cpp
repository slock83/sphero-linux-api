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

answerUnion_t* SpheroAnswerPacket::getAnswer(uint8_t seq)
{
	answerUnion_t* answer = _sequence_array[seq].front();

	_sequence_array[seq].pop();

	return answer;
}

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

void SpheroAnswerPacket::setAnswer(uint8_t seq, answerUnion_t* answer)
{
	_sequence_array[seq].push(answer);
}


