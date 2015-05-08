/*************************************************************************
	Toolbox  -  A bunch of useful functions for packet processing
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Boite à outils <Toolbox> (fichier Toolbox.hpp) ------
#ifndef ( TOOLBOX_HPP )
#define TOOLBOX_HPP

//-------------------------------------------------------- System includes
#include <cstdint>
#include <cstddef>

//-------------------------------------------------------------- Functions
namespace packet_toolbox
{
	/**
	 * @brief checksum : Computes a checksum
	 * @param packet_data : The packet data on which checksum will be computed
	 * @param len : Data array length
	 */
    uint8_t checksum(uint8_t* packet_data, size_t len);
}

#endif //TOOLBOX_HPP
