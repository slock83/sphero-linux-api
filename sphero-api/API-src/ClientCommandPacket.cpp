/*************************************************************************
                           ClientCommandPacket  -  description
                             -------------------
    début                : sam. 14 mars 2015
 *************************************************************************/

//Réalisation de la classe <ClientCommandPacket> (fichier ClientCommandPacket.cpp)

#include "ClientCommandPacket.h"

#include <stddef.h>
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
