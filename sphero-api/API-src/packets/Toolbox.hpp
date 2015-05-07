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
    uint8_t checksum(uint8_t did,
        uint8_t cid,
        uint8_t seq,
        uint8_t dlen,
        uint8_t* data);
}

#endif //TOOLBOX_HPP
