/*************************************************************************
   SpheroCollisionPacket  - Represents an asynchronous collision packet
                             -------------------
	started                : 07/05/2015
*************************************************************************/

#ifndef SPHEROCOLLISIONPACKET_H
#define SPHEROCOLLISIONPACKET_H

//--------------------------------------------------------- Local includes
#include "../SpheroAsyncPacket.hpp"


//------------------------------------------------------- Class definition
class SpheroCollisionPacket : public SpheroAsyncPacket 
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
		SpheroCollisionPacket& operator=(
				const SpheroCollisionPacket& unSpheroCollisionPacket) = delete;


		//---------------------------------------- Constructors/Destructor
			//No sense
		SpheroCollisionPacket(
				const SpheroCollisionPacket& unSpheroCollisionPacket) = delete;


		virtual ~SpheroCollisionPacket();


	protected:

		/**
		 * @brief SpheroCollisionPacket : Constructor
		 * @param sphero : The Sphero instance that sends the collision packet
		 */
		SpheroCollisionPacket(Sphero* sphero);
};

#endif // SPHEROCOLLISIONPACKET_H

