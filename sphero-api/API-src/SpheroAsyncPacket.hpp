

/*************************************************************************
    SpheroAsyncPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroAsyncPacket> (fichier SpheroAsyncPacket.hpp) ------
#if ! defined ( SPHEROASYNCPACKET_H )
#define SPHEROASYNCPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include "SpheroPacket.hpp"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroAsyncPacket>
//
// Définir les comportements des paquets asynchrones reçus par sphero
//------------------------------------------------------------------------ 

class SpheroAsyncPacket : public SpheroPacket
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
   	static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);
    virtual void packetAction() = 0;

//------------------------------------------------- Surcharge d'opérateurs
    SpheroAsyncPacket & operator = ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;


//-------------------------------------------- Constructeurs - destructeur

    SpheroAsyncPacket ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;

    virtual ~SpheroAsyncPacket();
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    SpheroAsyncPacket(Sphero* sphero);

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	static extractorMap_t _extractorMap;	
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <SpheroAsyncPacket>

#endif // SpheroAsyncPacket_H

