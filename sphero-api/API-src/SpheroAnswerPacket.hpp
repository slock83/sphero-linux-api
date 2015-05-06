

/*************************************************************************
    SpheroAnswerPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroAnswerPacket> (fichier SpheroAnswerPacket.hpp) ------
#if ! defined ( SPHEROANSWERPACKET_H )
#define SPHEROANSWERPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include "SpheroPacket.hpp"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroAnswerPacket>
//
// Définir les comportements des paquets "réponses" reçus par sphero
//------------------------------------------------------------------------ 

class SpheroAnswerPacket : public SpheroPacket
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
   	static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);
    virtual void packetAction() = 0;

//------------------------------------------------- Surcharge d'opérateurs
    SpheroAnswerPacket& operator=(const SpheroAnswerPacket& unSpheroAnswerPacket) = delete;


//-------------------------------------------- Constructeurs - destructeur
    SpheroAnswerPacket(const SpheroAnswerPacket& unSpheroAnswerPacket) = delete;

    virtual ~SpheroAnswerPacket();
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    SpheroAnswerPacket(Sphero* sphero);

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

//----------------------------------------- Types dépendants de <SpheroAnswerPacket>

#endif // SpheroAnswerPacket_H

