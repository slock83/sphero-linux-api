/*************************************************************************
   SpheroStreamingPacket  - Represents an asynchronous data streaming packet
							 -------------------
	started                : 17/05/2015
*************************************************************************/

#ifndef SPHEROSTREAMINGPACKET_H
#define SPHEROSTREAMINGPACKET_H

//-------------------------------------------------------- System includes
#include <vector>
using namespace std;

//--------------------------------------------------------- Local includes
#include "../SpheroAsyncPacket.hpp"
#include "DataBuffer.h"


class SpheroStreamingPacket : public SpheroAsyncPacket
{
	public:
		//------------------------------------------------- Public methods

		/**
		 * @brief extractPacket : extracts the packet from a socket
		 * @param fd : The socket file descriptor
		 * @param sphero : The Sphero sending the packet
		 * @param packet_ptr : A pointer to a SpheroPacket pointer
		 * @return true if the packet was successfully extracted from the
		 * 		   socket, false otherwise
		 *
		 * Contract: the socket has to be in blocking read
		 */
		static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);


		/**
		 * @brief packetAction : Performs the action associated to the packet
		 *			on the Sphero instance
		 */
		virtual void packetAction();


		//--------------------------------------------- Operators overload
			//No sense
		SpheroStreamingPacket& operator=(
				const SpheroStreamingPacket& unSpheroStreamingPacket) = delete;


		//---------------------------------------- Constructors/Destructor
			//No sense
		SpheroStreamingPacket(
				const SpheroStreamingPacket& unSpheroStreamingPacket) = delete;


		virtual ~SpheroStreamingPacket();


	protected:

		/**
		 * @brief SpheroStreamingPacket : Constructor
		 * @param sphero : The Sphero instance that sends the collision packet
		 */
		SpheroStreamingPacket(Sphero* sphero);
};

#endif // SPHEROSTREAMINGPACKET_H
