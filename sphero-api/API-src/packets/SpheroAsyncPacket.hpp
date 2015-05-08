/*************************************************************************
	SpheroAsyncPacket - Defines asynchronous packets behavior received by Sphero
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

#ifndef ( SPHEROASYNCPACKET_H )
#define SPHEROASYNCPACKET_H

//--------------------------------------------------------- Local includes
#include "SpheroPacket.hpp"

//-------------------------------------------------------------- Constants
#define POWER_NOTIFICATION_FLAG 0x1;
#define LVL_1_DIAGNOSTIC_RESPONSE 0x2;
#define SENSOR_DATA_STREAMING 0x3;
#define CONFIG_BLOCK_CONTENT 0x4;
#define PRESLEEP_WARNING 0x5;
#define MACRO_MARKERS 0x6;
#define COLLISION_DETECTED 0x7;
#define ORBBASIC_PRINT_MESSAGE 0x8;
#define ORBBASIC_ASCII_ERROR 0x9;
#define ORBBASIC_BINARY_ERROR 0xA;
#define SELF_LEVEL_RESULT 0xB;
#define GYRO_AXIS_LIMIT_EXCEEDED 0xC;


class SpheroAsyncPacket : public SpheroPacket
{
	public:
		//-------------------------------------------- Operators overload

		SpheroAsyncPacket & operator = ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;


		//--------------------------------------- Constructors/Destructor

		SpheroAsyncPacket ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;

		virtual ~SpheroAsyncPacket();


		//------------------------------------------------ Public methods

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

		/**
		 * @brief SpheroAnswerPacket : Constructor
		 * @param sphero : The Sphero instance that sends the asynchronous answer packet
		 */
		SpheroAsyncPacket(Sphero* sphero);

	private:

		static extractorMap_t _extractorMap;
	};

#endif //SPHEROASYNCPACKET_H

