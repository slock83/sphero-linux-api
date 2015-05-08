/******************************************************************************
    ActionHandler  - Template générique de gestion des différentes actions 
                             -------------------
    					   started on  : 05/08/2015
******************************************************************************/

//--- Interface de la classe <ActionHandler> (fichier ActionHandler.hpp) ------
#if ! defined ( ACTIONHANDLER_HPP )
#define ACTIONHANDLER_HPP

//--------------------------------------------------- Interfaces utilisées
#include <queue>
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
template<typename T>
typedef void (listener<T>*)(T);

/**
 * T : type de la structure de donnée qui sera communiquée à tous les listener
 */
template<typename T>
class ActionHandler 
{
//----------------------------------------------------------------- PUBLIC

public :
//----------------------------------------------------- Méthodes publiques
	/**
	 * @brief reportAction : Permet de tenir l'actionHandler au courant de 
	 * 						 l'action survenue. Tous les listener sont ensuite
	 * 						 notifiés.
	 * @param action : 	Un pointeur sur la structure de donnée qui contient
	 * 					les informations relatives à l'action.
	 */
	void reportAction(T action);

	/**
	 * @brief addActionListener : Permet d'enregistrer un listener d'action
	 * @param : listener : le listener à ajouter
	 */
	void addActionListener(listener<T> const listener);

	/**
	 * @brief clearListener : désenregistre tous les listeners
	 */
	void clearListener();

//------------------------------------------------- Surcharge d'opérateurs
    ActionHandler& operator=(const ActionHandler&) = delete;

//-------------------------------------------- Constructeurs - destructeur
    ActionHandler(const ActionHandler&) = delete;

    ActionHandler();

    virtual ~ActionHandler();

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	std::queue<listener<T> const> _listenerQueue;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <ActionHandler>
#include "ActionHandler.tpp"
#endif // ACTIONHANDLER_HPP

