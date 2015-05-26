/*************************************************************************
   SpheroSimpleStreamingPacket  - Represents an asynchronous data streaming packet
							 -------------------
	started                : 17/05/2015
*************************************************************************/

#ifndef SPHEROSIMPLESTREAMINGPACKET_H
#define SPHEROSIMPLESTREAMINGPACKET_H

//-------------------------------------------------------- System includes
#include <vector>
using namespace std;

//--------------------------------------------------------- Local includes
#include "../SpheroAsyncPacket.hpp"


class SpheroSimpleStreamingPacket : public SpheroAsyncPacket
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
		SpheroSimpleStreamingPacket& operator=(
				const SpheroSimpleStreamingPacket& unSpheroSimpleStreamingPacket) = delete;


		//---------------------------------------- Constructors/Destructor
			//No sense
		SpheroSimpleStreamingPacket(
				const SpheroSimpleStreamingPacket& unSpheroSimpleStreamingPacket) = delete;


		SpheroSimpleStreamingPacket(Sphero* sphero, int16_t x, int16_t y,
				int16_t speedX, int16_t speedY);

		virtual ~SpheroSimpleStreamingPacket();


	protected:

		/**
		 * @brief SpheroSimpleStreamingPacket : Constructor
		 * @param sphero : The Sphero instance that sends the collision packet
		 */
		SpheroSimpleStreamingPacket(Sphero* sphero);

	private:

		int16_t _x, _y, _speedX, _speedY;
};

#endif // SPHEROSIMPLESTREAMINGPACKET_H

