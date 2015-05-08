/*************************************************************************
    Toolbox  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Boite à outils <Toolbox> (fichier Toolbox.hpp) ------
#if ! defined ( TOOLBOX_HPP )
#define TOOLBOX_HPP

//--------------------------------------------------- Interfaces utilisées
#include <cstdint>
#include <cstddef>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------- Procédures
namespace packet_toolbox
{
	/**
	 * @brief checksum : Calcul une checksum
	 * @param packet_data : Les données du packet sur lesquelles calculer
	 * 						la checksum
	 * @param len : la taille du tableau packet_data
	 */
    uint8_t checksum(uint8_t* packet_data, size_t len);
}

#endif //TOOLBOX_HPP
