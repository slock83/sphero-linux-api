/*************************************************************************
    Toolbox  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Réalisation <Toolbox> (fichier Toolbox.hpp) ------

#include "Toolbox.hpp"

uint8_t packet_toolbox::checksum(uint8_t did,
		uint8_t cid,
		uint8_t seq,
		uint8_t dlen,
		uint8_t* data)
{
	uint8_t checksum;

	checksum = did;
	checksum += cid;
	checksum += seq;
	checksum += dlen;

	//dlen - 1 car dlen compte aussi la taille de la checksum
	for(size_t i = 0 ; i + 1 < dlen ; checksum += data[i++] )
	{ }

	//Inversion de la somme obtenue
	checksum ^= 0xFF;

	return checksum;
}
