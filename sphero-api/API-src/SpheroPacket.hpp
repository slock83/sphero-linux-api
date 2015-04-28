/*************************************************************************
                           SpheroPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
    copyright            : (C) 2015 par B3253 - L. Forget - F. Meyer
*************************************************************************/

//---------- Interface de la classe <SpheroPacket> (fichier SpheroPacket.hpp) ------
#if ! defined ( SPHEROPACKET_H )
#define SPHEROPACKET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroPacket>
//
//
//------------------------------------------------------------------------ 

class SpheroPacket
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs
    SpheroPacket & operator = ( const SpheroPacket & unSpheroPacket ) = delete;


//-------------------------------------------- Constructeurs - destructeur
    SpheroPacket ( const SpheroPacket & unSpheroPacket ) = delete;

    SpheroPacket();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~SpheroPacket();
    // Mode d'emploi :
    //
    // Contrat :
    //

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

//----------------------------------------- Types dépendants de <SpheroPacket>

#endif // SPHEROPACKET_H

