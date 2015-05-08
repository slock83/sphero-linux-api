/*************************************************************************
	SpheroAsyncPacket - Defines asynchronous packets behavior received by Sphero
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

#ifndef SPHEROASYNCPACKET_H
#define SPHEROASYNCPACKET_H

//--------------------------------------------------------- Local includes
#include "SpheroPacket.hpp"

//-------------------------------------------------------------- Constants
static const uint8_t POWER_NOTIFICATION_FLAG = 0x1;
static const uint8_t LVL_1_DIAGNOSTIC_RESPONSE = 0x2;
static const uint8_t SENSOR_DATA_STREAMING = 0x3;
static const uint8_t CONFIG_BLOCK_CONTENT = 0x4;
static const uint8_t PRESLEEP_WARNING = 0x5;
static const uint8_t MACRO_MARKERS = 0x6;
static const uint8_t COLLISION_DETECTED = 0x7;
static const uint8_t ORBBASIC_PRINT_MESSAGE = 0x8;
static const uint8_t ORBBASIC_ASCII_ERROR = 0x9;
static const uint8_t ORBBASIC_BINARY_ERROR = 0xA;
static const uint8_t SELF_LEVEL_RESULT = 0xB;
static const uint8_t GYRO_AXIS_LIMIT_EXCEEDED = 0xC;


//------------------------------------------------------- Class definition
class SpheroAsyncPacket : public SpheroPacket
{
	public:
		//-------------------------------------------- Operators overload
			//No sense
		SpheroAsyncPacket & operator = ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;


		//--------------------------------------- Constructors/Destructor
			//No sense
		SpheroAsyncPacket ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;

		virtual ~SpheroAsyncPacket();

		//------------------------------------------------ Public methods

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

		/**
		 * @brief SpheroAnswerPacket : Constructor
		 * @param sphero : The Sphero instance that receives the asynchronous answer packet
		 */
		SpheroAsyncPacket(Sphero* sphero);

	private:

		static extractorMap_t _extractorMap;
	};

#endif //SPHEROASYNCPACKET_H

