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
#include "utils/byte-utils.hpp"

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

	_chk = _did;
	_chk += cid;
	_chk += seq;
	_chk += dlen;

	//dlen - 1 car dlen compte aussi la taille de la checksum
	for(size_t i = 0 ; i+1 < _dlen ; _chk += data[i++] )
		//Bloc vide
	{
	}

	//Inversion de la somme obtenue
	_chk ^= 0xFF;
}

uint8_t* ClientCommandPacket::toByteArray()
{
	uint8_t array[6+_dlen];
	array[0] = _sop1;
	array[1] = _sop2;
	array[3] = _did;
	array[4] = _cid;
	array[5] = _seq;
	array[6] = _dlen;
	for(int i = 0 ; i+1 < _dlen ; ++i)
	{
		array[7+i] = _data[i];
	}
	array[6+_dlen] = _chk;
	return array;
}

size_t ClientCommandPacket::getSize()
{
	return _dlen+6;
}
