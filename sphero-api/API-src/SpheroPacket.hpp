/*************************************************************************
    SpheroPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroPacket> (fichier SpheroPacket.hpp) ------
#if ! defined ( SPHEROPACKET_H )
#define SPHEROPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include "Sphero.hpp"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

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
    // <!--- Question : Virtual pure ?? -->
    virtual void extractPacket(int fd) = 0;

    // Effectue l'action associée au paquet sur l'instance
    // du Sphero passée en paramètre.
    virtual void packetAction(Sphero* sphero) = 0;

//------------------------------------------------- Surcharge d'opérateurs
    SpheroPacket & operator = ( const SpheroPacket & unSpheroPacket ) = delete;

//-------------------------------------------- Constructeurs - destructeur
    SpheroPacket() : _packet(nullptr) {};

    SpheroPacket ( const SpheroPacket & unSpheroPacket ) = delete;

    virtual ~SpheroPacket() {};
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    ClientCommandPacket* _packet;
private:
//------------------------------------------------------- Attributs privés
	
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <SpheroPacket>

#endif // SPHEROPACKET_H

