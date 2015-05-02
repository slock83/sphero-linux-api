

/*************************************************************************
    SpheroAsyncPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroAsyncPacket> (fichier SpheroAsyncPacket.hpp) ------
#if ! defined ( SPHEROASYNCPACKET_H )
#define SPHEROASYNCPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include "ShperoPacket.hpp"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroAsyncPacket>
//
// Définir les comportements des paquets asynchrones reçus par sphero
//------------------------------------------------------------------------ 

class SpheroAsyncPacket
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
    virtual extractPacket(int fd);
    virtual packetAction(Sphero* sphero);

//------------------------------------------------- Surcharge d'opérateurs
    SpheroAsyncPacket & operator = ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;


//-------------------------------------------- Constructeurs - destructeur
    SpheroAsyncPacket();

    SpheroAsyncPacket ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;

    virtual ~SpheroAsyncPacket();
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    

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

//----------------------------------------- Types dépendants de <SpheroAsyncPacket>

#endif // SpheroAsyncPacket_H

