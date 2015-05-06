/*************************************************************************
                           SpheroAnswerPacket  -  description
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//------ Réalisation de la classe <SpheroAnswerPacket> (fichier SpheroAnswerPacket.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sys/select.h>
#include <fcntl.h>

//------------------------------------------------------ Include personnel
#include "SpheroAnswerPacket.hpp"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
SpheroAnswerPacket::SpheroAnswerPacket(Sphero* sphero) : SpheroPacket(sphero)
{

}

SpheroAnswerPacket::~SpheroAnswerPacket()
{

}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées


