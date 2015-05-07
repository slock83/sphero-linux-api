/*************************************************************************
                           ClientCommandPacket  -  description
                             -------------------
    début                : sam. 14 mars 2015
 *************************************************************************/

//Réalisation de la classe <ClientCommandPacket> (fichier ClientCommandPacket.cpp)

#include "ClientCommandPacket.hpp"

#include <cstddef>
#include <sstream>
#include <iostream>
#include "../utils/Toolbox.hpp"

using namespace std;

ClientCommandPacket::ClientCommandPacket(
		byte did,
		byte cid,
		byte seq,
		byte dlen,
		byte* data,
		bool acknowledge,
		bool rstTO
):_sop1(INIT_SOP1),
_sop2(INIT_SOP2),
_did(did),
_cid(cid),
_seq(seq),
_dlen(dlen),
_data(data)
{
	if(acknowledge)
	{
		_sop2 ^= ANS_FLAG;
	}

	if(rstTO)
	{
		_sop2 ^= RST_FLAG;
	}

	_chk = packet_toolbox::checksum(did, cid, seq, dlen, data);

#ifdef MAP
	std::cout << "Checksum :" << (unsigned int) _chk << std::endl;
#endif
	array = new uint8_t[6 + _dlen];
}

ClientCommandPacket::~ClientCommandPacket()
{
	delete array;
}

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
#ifdef MAP
	for(size_t i = 0 ; i < _dlen + 6 ; ++i)
	{
		std::cout <<
			"array[" << i << "] = " << (unsigned int) array[i] << std::endl;
	}
#endif
	return array;
}

size_t ClientCommandPacket::getSize()
{
	return _dlen+6;
}
