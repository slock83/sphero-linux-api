/************************************************************************
    sphero  -  description
                             -------------------
    début                : lun. 16 mars 2015
 *************************************************************************/

//---------- Interface de la classe <sphero> (fichier sphero.h) ------
#if ! defined ( SPHERO_H )
#define SPHERO_H

//--------------------------------------------------- Interfaces utilisées
#include <string.h>
#include <cstdlib>
#ifdef BLUEZ
//Nécessaire plus bas
#include "bluetooth/bluez_adaptor.h"
#endif
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
typedef int16_t spherocoord_t;

class sphero_listener
{
public:
};

//------------------------------------------------------------------------ 
//T est un connecteur bluetooth
template<typename T>
class sphero 
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques


	//------------------------------------------------- Surcharge d'opérateurs
	//N'a pas de sens
	sphero & operator = ( const sphero & unsphero ) = delete;

	//-------------------------------------------- Constructeurs - destructeur
	//N'a pas de sens
	sphero ( const sphero & unsphero ) = delete;

	/*
	 * BT address (format : "XX:XX:XX:XX:XX:XX")
	 */
	sphero(char*  btaddr);

	virtual ~sphero ( );

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

private:
	//------------------------------------------------------- Méthodes privées

protected:
	//----------------------------------------------------- Attributs protégés

private:
	//------------------------------------------------------- Attributs privés
	T* _btManager;

	/*
	 * X accelerometer
	 */
	spherocoord_t accelerometer_x;

	/*
	 * Y accelerometer
	 */
	spherocoord_t accelerometer_y;

	/*
	 * Z accelerometer
	 */
	spherocoord_t accelerometer_z;

	//To be continued


	//---------------------------------------------------------- Classes amies

	//-------------------------------------------------------- Classes privées
	class sphero_listener : public bluetooth_listener
	{
		virtual void manage_data(size_t data_length, uint8_t* data);	
	};

	//----------------------------------------------------------- Types privés
};

#include "sphero.tpp"

//----------------------------------------- Types dépendants de <sphero>
#ifdef BLUEZ
typedef sphero<bluez_adaptor> sphero;
#endif
#endif // SPHERO_H

