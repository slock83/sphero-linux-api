/*************************************************************************
   ClientCommandPacket  
                             -------------------
    début                : sam. 14 mars 2015
*************************************************************************/

// Interface de la classe <ClientCommandPacket> (fichier ClientCommandPacket.h)
#if ! defined ( CLIENTCOMMANDPACKET_H )
#define CLIENTCOMMANDPACKET_H

#include <stdint.h>
#include <string>

//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------------ Types 
typedef uint8_t byte;

//------------------------------------------------------------------ Constantes
const byte ANS_FLAG = 0x01;
const byte RST_FLAG = 0x02;
const byte INIT_SOP1 = 0xFF;
//SOP2 is initialized with RST and ANS set to false
const byte INIT_SOP2 = 0xFC;

//------------------------------------------------------------------------ 
/*
 * Packets are sent from client to sphero in the following format
 * | SOP1 | SOP2 | DID | CID | SEQ | DLEN | <data> | CHK
 *
 * SOP1 : Start of Packet #1 -- Always FFh
 * SOP2 : Start of Packet #2 -- F8 to FFh encoding 4 bits of per-message 
 * 		 options (see below)
 *                   +-----+-----+-----+-----+-----+-----+-----+-----+
 *       Bits :      |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 *                   +-----+-----+-----+-----+-----+-----+-----+-----+
 *       Value:      |  1  |  1  |  1  |  1  |  1  |  1  | rst | ans |
 *                   +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *       when rst is set to 1 : reset client inactivity timeout
 *       when ans is set to 1 : client send reply after acting
 * 		  
 * DID : Device ID -- The virtual device this packet is intended for
 * CID : Command ID -- The command code
 * SEQ : Sequence Number -- This client field is echoed in the response for all
 *       synchronous commands (and ignored by Sphero when SOP2 has bit 0 clear)
 * DLEN : Data Length -- The number of bytes following through the end of the packet
 * <data> : Data -- Optional data to accompany the Command
 * CHK : Checksum -- The modulo 256 sum of all the bytes from the DID through 
 *       the end of the data payload, bit inverted (1's complement)
 *
*/ 
//
//------------------------------------------------------------------------ 

class ClientCommandPacket
{

public:

	ClientCommandPacket(
			byte did,
			byte cid,
			byte seq,
			byte dlen,
			byte* data,
			bool acknowledge = false,
			bool rstTO = false
		);

	std::string toString();

protected:

private:

protected:

private:
	/**
	 * Start of Packet 1
	 */
	byte _sop1 ;

	/**
	 * Start of packet 2
	 */
	byte _sop2;

	/**
	 * Virtual device id
	 */
	byte _did;

	/**
	 * Command id
	 */
	byte _cid;

	/**
	 * Sequence identifier (client field)
	 */
	byte _seq;

	/**
	 * Data length
	 */
	byte _dlen;

	/**
	 * Optional data to accompany the command
	 */
	byte* _data;

	/**
	 * Checksum
	 */
	byte _chk;

};

//----------------------------------------- Types dépendants de <ClientCommandPacket>

#endif // CLIENTCOMMANDPACKET_H

