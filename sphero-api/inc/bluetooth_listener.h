/*************************************************************************
    bluetooth_listener
                             -------------------
    début                : mar. 17 mars 2015
*************************************************************************/

//---------- Interface de la classe <bluetooth_listener> (fichier bluetooth_listener.h) ------
#if ! defined ( BLUETOOTH_LISTENER_H )
#define BLUETOOTH_LISTENER_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 

class bluetooth_listener 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	virtual void manage_data(size_t data_length, uint8_t* data) = 0;	

//------------------------------------------------- Surcharge d'opérateurs
    bluetooth_listener & operator = ( const bluetooth_listener & unbluetooth_listener ) = delete;	

//-------------------------------------------- Constructeurs - destructeur
    bluetooth_listener ( const bluetooth_listener & unbluetooth_listener ) = delete;

    virtual ~bluetooth_listener ( );

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

//----------------------------------------- Types dépendants de <bluetooth_listener>

#endif // BLUETOOTH_LISTENER_H

