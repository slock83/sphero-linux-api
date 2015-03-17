/*************************************************************************
                           ClientCommandPacket  -  description
                             -------------------
    début                : sam. 14 mars 2015
 *************************************************************************/

//Réalisation de la classe <ClientCommandPacket> (fichier ClientCommandPacket.cpp)

#include "../inc/ClientCommandPacket.h"
#include <cstdlib>

ClientCommandPacket::ClientCommandPacket(
		field did,
		field cid,
		field seq,
		field dlen,
		field* data,
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
