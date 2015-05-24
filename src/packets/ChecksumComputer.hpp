/*************************************************************************
                           ChecksumComputer  -  description
                             -------------------
    début                : dim. 24 mai 2015
*************************************************************************/

//--------- Interface de la classe <ChecksumComputer> (fichier ChecksumComputer.hpp) ------
#if ! defined ( CHECKSUMCOMPUTER_H )
#define CHECKSUMCOMPUTER_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

class ChecksumComputer
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs
    ChecksumComputer & operator = ( const ChecksumComputer & unChecksumComputer) = delete;
	uint8_t operator()();

//-------------------------------------------- Constructeurs - destructeur
    ChecksumComputer ( const ChecksumComputer & unChecksumComputer ) = delete;

    ChecksumComputer( );

    virtual ~ChecksumComputer ( );
	void addField(uint8_t* table, size_t length);
	void addField(uint8_t field);

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	uint8_t _sum;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <ChecksumComputer>

#endif // CHECKSUMCOMPUTER_H

