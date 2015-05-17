/*************************************************************************
	SpheroAnswerPacket  -  Defines the behavior of
									"answer" packets received by Sphero
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

#ifndef SPHEROANSWERPACKET_H
#define SPHEROANSWERPACKET_H

//--------------------------------------------------------- Local includes
#include "SpheroPacket.hpp"

#include <queue>

#include "answer/ColorStruct.hpp"

//-------------------------------------------------------------- Constants

//------------------------------------------------------------------ Types

union answerUnion_t
{
	ColorStruct* color;
};

//------------------------------------------------------- Class definition
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

		static answerUnion_t* getAnswer(uint8_t seq);

		/**
		 * @brief extractPacket : extracts the packet from a socket
		 * @param fd : The socket file descriptor
		 * @param sphero : The Sphero sending the packet
		 * @param packet_ptr : A pointer to a SpheroPacket pointer
		 * @return true if the packet was successfully extracted from the socket, false otherwise
		 *
		 * Contract: the socket has to be in blocking read
		 */
		static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);

		/**
		 * @brief packetAction : Performs the action associated to the packet
		 *			on the Sphero instance
		 */
		virtual void packetAction() = 0;

	protected:

		//--------------------------------------------- Protected methods
		
		static void setAnswer(uint8_t seq, answerUnion_t* answer);
	
		//-------------------------------------------------- Constructors

		/**
		 * @brief SpheroAnswerPacket : Constructor
		 * @param sphero : The Sphero instance that receives the answer packet
		 */
		SpheroAnswerPacket(Sphero* sphero);

	private:
		static std::queue<answerUnion_t*> _sequence_array[256];

	    static extractorMap_t _extractorMap;
};

#endif // SpheroAnswerPacket_H

