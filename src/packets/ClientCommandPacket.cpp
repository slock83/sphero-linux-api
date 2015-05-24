/*************************************************************************
	 ClientCommandPacket  -  The packet creator used for every
						   command sent by the client to the Sphero
                             -------------------
    début                : sam. 14 mars 2015
 *************************************************************************/

//--------------------------------------------------------- System includes
#include <cstddef>
#include <sstream>
#include <iostream>

using namespace std;

//---------------------------------------------------------- Local includes
#include "ClientCommandPacket.hpp"
#include "Toolbox.hpp"

//------------------------------------------------- Constructors/Destructor

/**
 * @brief ClientCommandPacket : Constructor
 * @param did : Device ID -- The virtual device this packet is intended for
 * @param cid : Command ID -- The command code
 * @param seq : SEQ : Sequence Number -- This client field is echoed in the response for all
 *       synchronous commands (and ignored by Sphero when SOP2 has bit 0 clear)
 * @param dlen : Data Length -- The number of bytes following through the end of the packet
 * @param data : Data -- Optional data to accompany the Command
 * @param acknowledge : if true, client send reply after acting
 * @param rstTO : if true, reset client inactivity timeout
 */
ClientCommandPacket::ClientCommandPacket(byte did, byte cid, byte seq, byte dlen,
										 byte* data, bool acknowledge, bool rstTO):
			_sop1(INIT_SOP1), _sop2(INIT_SOP2), _did(did), _cid(cid),
			_seq(seq), _dlen(dlen), _data(data)
{
	if(acknowledge)
	{
		_sop2 ^= ANS_FLAG;
	}

	if(rstTO)
	{
		_sop2 ^= RST_FLAG;
	}

	uint8_t* packet_data = new uint8_t[4 + _dlen - 1];
	
	packet_data[0] = _did;
	packet_data[1] = _cid;
	packet_data[2] = _seq;
	packet_data[3] = _dlen;
	
    for(size_t i = 0; i+1 < _dlen ; packet_data[i + 4] = _data[i], i++)
	{}
	
	_chk = packet_toolbox::checksum(packet_data, 4 + _dlen - 1);
	
	delete packet_data;

#ifdef MAP
	std::cout << "Checksum :" << (unsigned int) _chk << std::endl;
#endif
	array = new uint8_t[6 + _dlen];
}


ClientCommandPacket::~ClientCommandPacket()
{
	delete array;
}


//---------------------------------------------------------- Public methods

/**
 * @brief toByteArray : transforms the packet data into a single array
 * @return the array containing the final packet structure
 */
uint8_t* ClientCommandPacket::toByteArray()
{
	array[0] = _sop1;
	array[1] = _sop2;
	array[2] = _did;
	array[3] = _cid;
	array[4] = _seq;
	array[5] = _dlen;

	for(int i = 0 ; i < _dlen-1 ; ++i)
	{
		array[6+i] = _data[i];
	}

	array[6+_dlen-1] = _chk;

	return array;
}


/**
 * @return The final packet size
 */
size_t ClientCommandPacket::getSize()
{
	return _dlen+6;
}
