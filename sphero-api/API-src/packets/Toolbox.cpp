/*************************************************************************
    Toolbox  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Réalisation <Toolbox> (fichier Toolbox.hpp) ------

#include "Toolbox.hpp"

/**
 * @brief checksum : Calcul une checksum
 * @param packet_data : Les données du packet sur lesquelles calculer
 * 						la checksum
 * @param len : la taille du tableau packet_data
 */
uint8_t packet_toolbox::checksum(uint8_t* packet_data, size_t len)
{
	uint8_t checksum = 0;

	for(size_t i = 0 ; i < len ; checksum += packet_data[i++])
	{ }

	//Inversion de la somme obtenue
	checksum ^= 0xFF;

	return checksum;
}