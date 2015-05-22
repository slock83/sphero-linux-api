/*************************************************************************
	Toolbox  -  A bunch of useful functions for packet processin
                             -------------------
	started                : 28/04/2015
*************************************************************************/

//--------------------------------------------------------- Local includes
#include "Toolbox.hpp"


//-------------------------------------------------------------- Functions

/**
 * @brief checksum : Computes a checksum
 * @param packet_data : The packet data on which checksum will be computed
 * @param len : Data array length
 */
uint8_t packet_toolbox::checksum(uint8_t* packet_data, size_t len)
{
	uint8_t checksum = 0;

	for(size_t i = 0 ; i < len ; checksum += packet_data[i++])
	{ }

		//Inverting result sum
	checksum ^= 0xFF;

	return checksum;
}
