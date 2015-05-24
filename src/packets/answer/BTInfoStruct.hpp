/*************************************************************************
    BTInfoStruct  
                             -------------------
    début                : dim. 24 mai 2015
*************************************************************************/

//--------- Interface de la classe <BTInfoStruct> (fichier BTInfoStruct.hpp) ------
#if ! defined ( BTINFOSTRUCT_H )
#define BTINFOSTRUCT_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 

struct BTInfoStruct 
{
//----------------------------------------------------------------- PUBLIC
	
	/**
	 * @field bt_name Ascii encoded bluetooth name
	 */
	std::string bt_name;

	/**
	 * @field bt_adress Ascii encoded bluetooth adress
	 */
	std::string bt_adress;

};

//----------------------------------------- Types dépendants de <BTInfoStruct>

#endif // BTINFOSTRUCT_H

