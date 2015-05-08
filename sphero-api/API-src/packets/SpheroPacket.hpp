/*************************************************************************
	SpheroPacket  -  Abstract class. Defines the behavior of
												packets received by Sphero
                             -------------------
	started                : 28/04/2015
*************************************************************************/

#ifndef ( SPHEROPACKET_H )
#define SPHEROPACKET_H

//-------------------------------------------------------- System includes
#include <unordered_map>

//--------------------------------------------------------- Local includes
#include "../Sphero.hpp"

//-------------------------------------------------------------- Constants
#define START_OF_PACKET_FLAG 0xFF;
#define ASYNC_FLAG  0xFE;
#define ANSWER_FLAG 0xFF;

//------------------------------------------------------------------ Types 
class SpheroPacket;

typedef bool (*packetExtractor)(int socketd, Sphero* sphero, SpheroPacket** packet_ptr);
typedef std::unordered_map<uint8_t, packetExtractor> extractorMap_t;
typedef std::pair<uint8_t, packetExtractor> extractorMapEntry_t;


//------------------------------------------------------- Class definition
class SpheroPacket
{
	public:
		//--------------------------------------------- Operators overload
			//No sense
		SpheroPacket& operator=(const SpheroPacket&) = delete;

		//---------------------------------------- Constructors/Destructor
			//No sense
		SpheroPacket(const SpheroPacket&) = delete;

		virtual ~SpheroPacket();

		//------------------------------------------------ Public methods

		/**
		 * @brief extractPacket : extracts informations from the file descriptor to build a well made packet
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

		/**
		 * @brief SpheroPacket::SpheroPacket
		 * @param sphero : The Sphero instance that receives the packet
		 */
		SpheroPacket(Sphero* sphero);

		//------------------------------------------ Protected attributes
		Sphero* _sphero;

	private:
		static extractorMap_t _extractorMap;
};

#endif // SPHEROPACKET_H

