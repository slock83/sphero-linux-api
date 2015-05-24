/*************************************************************************
                           ChecksumComputer  -  description
                             -------------------
    début                : dim. 24 mai 2015
*************************************************************************/

//---------- Réalisation de la classe <ChecksumComputer> (fichier ChecksumComputer.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

using namespace std;
//------------------------------------------------------ Include personnel
#include "ChecksumComputer.hpp"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
void ChecksumComputer::addField(uint8_t* table, size_t length)
{
	for(size_t i = 0 ; i < length ; ++i)
	{
		_sum = (_sum + table[i]) % 256;
	}
}
void ChecksumComputer::addField(uint8_t field)
{
	_sum = (_sum + field) % 256;
}

//------------------------------------------------- Surcharge d'opérateurs
uint8_t ChecksumComputer::operator()(void)
{
	return ~_sum;
}
//-------------------------------------------- Constructeurs - destructeur
ChecksumComputer::ChecksumComputer ( ):_sum(0)
{
} 


ChecksumComputer::~ChecksumComputer ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <ChecksumComputer>" << endl;
#endif
} 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

