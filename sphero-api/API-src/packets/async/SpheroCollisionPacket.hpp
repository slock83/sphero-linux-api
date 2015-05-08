/*************************************************************************
   SpheroCollisionPacket  - Représente un paquet asynchrone de collision 
                             -------------------
    début                : jeu. 07 mai 2015
*************************************************************************/

//---------- Interface de la classe <SpheroCollisionPacket> (fichier SpheroCollisionPacket.hpp) ------
#if ! defined ( SPHEROCOLLISIONPACKET_H )
#define SPHEROCOLLISIONPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include "../SpheroAsyncPacket.hpp"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 

//------------------------------------------------------------------------ 

class SpheroCollisionPacket : public SpheroAsyncPacket 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
   	static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);
    virtual void packetAction();

//------------------------------------------------- Surcharge d'opérateurs
    SpheroCollisionPacket& operator=(
			const SpheroCollisionPacket& unSpheroCollisionPacket) = delete;


//-------------------------------------------- Constructeurs - destructeur
    SpheroCollisionPacket(
			const SpheroCollisionPacket& unSpheroCollisionPacket) = delete;

    virtual ~SpheroCollisionPacket ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    SpheroCollisionPacket(Sphero* sphero);

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//-------------------------------- Types dépendants de <SpheroCollisionPacket>

#endif // SPHEROCOLLISIONPACKET_H

