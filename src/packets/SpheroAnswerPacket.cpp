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
#include "../Sphero.hpp"
#include "SpheroAnswerPacket.hpp"
#include "ChecksumComputer.hpp"

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
 * Contract: the socket has to be in blocking read mode
 */
bool SpheroAnswerPacket::extractPacket(int fd, Sphero* sphero, SpheroPacket**)
{
#ifdef MAP
	fprintf(stderr, "Answer packet reception\n\n");
#endif

	uint8_t msgrsp;
	uint8_t seq;
	uint8_t dlen;
	uint8_t* dataPayload = NULL;
	uint8_t checksum;
	
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

	rcvVal = recv(fd, &dlen, sizeof(dlen), 0);
	if(rcvVal != sizeof(seq))
	{
		return false;
	}

	if(dlen > 1)
	{
		dataPayload = (uint8_t*) malloc((dlen-1) * sizeof(uint8_t));
		rcvVal = recv(fd, dataPayload, dlen - 1, 0);
		if(rcvVal != sizeof(seq))
		{
			free(dataPayload);
			return false;
		}
	}
	
	rcvVal = recv(fd, &checksum, sizeof(checksum), 0);
	if(rcvVal != sizeof(checksum))
	{
		if(dataPayload != NULL)
		{
			free(dataPayload);
		}
		return false;
	}

	ChecksumComputer cc;
	cc.addField(seq);
	cc.addField(msgrsp);
	cc.addField(dlen);

	if(dataPayload != NULL)
	{
		cc.addField(dataPayload, dlen - 1);
	}

	if(cc() != checksum)
	{
#ifdef MAP
		fprintf(stderr, "Erreur de checksum\n");
#endif
		if(dataPayload != NULL)
		{
			free(dataPayload);
			return false;
		}
	}
	
#ifdef MAP
	fprintf(stdout, "msgrsp : %u ;\nseq : %u;\n", msgrsp, seq);
#endif

	sphero->lockSeqnum(seq);
	pendingCommandType requested = sphero->getTodo(seq);
	packetFormatter pf = getPacketFromTodo(requested);
	void* retour = pf(dlen, dataPayload);

	sphero->notifyPacket(seq, msgrsp, retour);
	
	sphero->unlockSeqnum(seq);
	
	if(dataPayload != NULL)
	{
		free(dataPayload);
	}

	return false;
}

//------------------------------------------------------------- Private methods

packetFormatter SpheroAnswerPacket::getPacketFromTodo(pendingCommandType todo)
{
	switch(todo){
		case GETCOLOR:
			return [](uint8_t dlen, uint8_t* dataPayload){
				if (dlen != 0x04)
				{
					return (void*) NULL;
				}
				ColorStruct* color = new ColorStruct;
				color->red = dataPayload[0];
				color->green = dataPayload[1];
				color->blue = dataPayload[2];
				return (void*) color;
			};
			break;
		case NONE:
		case SIMPLE_RESPONSE:
		default:
			return [](uint8_t, uint8_t* ){ return (void*) NULL; };
			break;
	}
}
