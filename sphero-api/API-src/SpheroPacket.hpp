/*************************************************************************
    SpheroPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroPacket> (fichier SpheroPacket.hpp) ------
#if ! defined ( SPHEROPACKET_H )
#define SPHEROPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include <unordered_map>
#include "Sphero.hpp"
//------------------------------------------------------------- Constantes 
static uint8_t const ASYNC_FLAG  = 0xFE;
static uint8_t const ANSWER_FLAG = 0xFF;

//------------------------------------------------------------------ Types 
class SpheroPacket;

typedef bool (*packetExtractor)(int socketd, Sphero* sphero, SpheroPacket** packet_ptr);
typedef std::unordered_map<uint8_t, packetExtractor> extractorMap_t;
typedef std::pair<uint8_t, packetExtractor> extractorMapEntry_t;

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroPacket>
//
// Classe abstraite
// Définir les comportements des paquets reçus par sphero
//------------------------------------------------------------------------ 

class SpheroPacket
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
    // Extrait les informations du descripteur de fichier
    // afin de construire un paquet bien formé.
   	static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);

    // Effectue l'action associée au paquet sur l'instance
    // du Sphero passée en paramètre.
    virtual void packetAction() = 0;

//------------------------------------------------- Surcharge d'opérateurs
    SpheroPacket& operator=(const SpheroPacket& unSpheroPacket) = delete;

//-------------------------------------------- Constructeurs - destructeur

    SpheroPacket(const SpheroPacket& unSpheroPacket) = delete;

    virtual ~SpheroPacket();
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    SpheroPacket(Sphero* sphero);
private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
	Sphero* _sphero;

private:
//------------------------------------------------------- Attributs privés
	static extractorMap_t _extractorMap;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <SpheroPacket>

#endif // SPHEROPACKET_H

