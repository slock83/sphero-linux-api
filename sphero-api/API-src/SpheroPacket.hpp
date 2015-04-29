/*************************************************************************
    SpheroPacket  -  description
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroPacket> (fichier SpheroPacket.hpp) ------
#if ! defined ( SPHEROPACKET_H )
#define SPHEROPACKET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
template<typename T>
class ISphero<T>;

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroPacket>
//
// Définir les comportements des paquets reçus par sphero
//------------------------------------------------------------------------ 

class SpheroPacket<Sphero>
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
	template<typename T>
	notify(T& sphero);

//------------------------------------------------- Surcharge d'opérateurs
    SpheroPacket & operator = ( const SpheroPacket & unSpheroPacket ) = delete;


//-------------------------------------------- Constructeurs - destructeur
    SpheroPacket ( const SpheroPacket & unSpheroPacket ) = delete;

    virtual ~SpheroPacket();
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    SpheroPacket();

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

