/*************************************************************************
	SpheroAnswerPacket  -  Defines the behavior of
									"answer" packets received by Sphero
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

#ifndef ( SPHEROANSWERPACKET_H )
#define SPHEROANSWERPACKET_H

//--------------------------------------------------------- Local includes
#include "SpheroPacket.hpp"


class SpheroAnswerPacket : public SpheroPacket
{
	public:
		//--------------------------------------------- Operators overload
			//No sense
		SpheroAnswerPacket& operator=(const SpheroAnswerPacket& unSpheroAnswerPacket) = delete;

		//---------------------------------------- Constructors/Destructor
			//No sense
		SpheroAnswerPacket(const SpheroAnswerPacket& unSpheroAnswerPacket) = delete;

		virtual ~SpheroAnswerPacket();

		//------------------------------------------------- Public methods

		/**
		 * @brief extractPacket : extracts the packet from a socket
		 * @param fd : The socket file descriptor
		 * @param sphero : The Sphero sending the packet
		 * @param packet_ptr : A pointer to a SpheroPacket pointer
		 * @return true if the packet was successfully extracted from the socket, false otherwise
		 */
		static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);

		/**
		 * @brief packetAction : Defines the packet behavior on reception
		 */
		virtual void packetAction() = 0;

	protected:

		//-------------------------------------------------- Constructors

		/**
		 * @brief SpheroAnswerPacket : Constructor
		 * @param sphero : The Sphero instance that sends the answer packet
		 */
		SpheroAnswerPacket(Sphero* sphero);

	private:

	   static extractorMap_t _extractorMap;

};

#endif // SpheroAnswerPacket_H

