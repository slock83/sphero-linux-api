/*************************************************************************
                           bluez_adaptor  -  description
                             -------------------
    début                : mar. 17 mars 2015
    copyright            : (C) 2015 par B3224 - L. Forget - V.Nouvellet
*************************************************************************/

//---------- Interface de la classe <bluez_adaptor> (fichier bluez_adaptor.h) ------
#if ! defined ( BLUEZ_ADAPTOR_H )
#define BLUEZ_ADAPTOR_H

//--------------------------------------------------- Interfaces utilisées
#include "bluetooth_connector.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
//
//------------------------------------------------------------------------ 

class bluez_adaptor : public bluetooth_connector
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	
	/**
	 * Établie la connexion
	 */
	virtual int connect();

	/**
	 * Permet l'envoi d'un flux de données au destinataire
	 */
	virtual int send_data(size_t data_length, uint8_t const * data);

	/**
	 * Ferme la connexion
	 */
	virtual int disconnect(void);

//------------------------------------------------- Surcharge d'opérateurs
	//N'a pas de sens
    bluez_adaptor & operator = ( const bluez_adaptor & unbluez_adaptor ) = delete;


//-------------------------------------------- Constructeurs - destructeur
    bluez_adaptor ( const bluez_adaptor & unbluez_adaptor ) = delete;

    bluez_adaptor (const char* address );

    virtual ~bluez_adaptor ( );

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

//----------------------------------------- Types dépendants de <bluez_adaptor>

#endif // BLUEZ_ADAPTOR_H

