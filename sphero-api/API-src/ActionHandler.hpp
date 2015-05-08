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
#include <functional>
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

/**
 * T : type de la structure de donnée qui sera communiquée à tous les listener
 */
template<typename ...T>
class ActionHandler 
{
//----------------------------------------------------------------- PUBLIC

public :
//--------------------------------------------------------- Types internes 
	using listener_t = std::function<void(T...)>;

//----------------------------------------------------- Méthodes publiques
	/**
	 * @brief reportAction : Permet de tenir l'actionHandler au courant de 
	 * 						 l'action survenue. Tous les listener sont ensuite
	 * 						 notifiés.
	 * @param action : 	Un pointeur sur la structure de donnée qui contient
	 * 					les informations relatives à l'action.
	 */
	void reportAction(T... action);

	/**
	 * @brief addActionListener : Permet d'enregistrer un listener d'action
	 * @param : listener : le listener à ajouter
	 */
	void addActionListener(listener_t listener);

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
//----------------------------------------------------------- Types privés
	using listenerQueue_t = std::queue<listener_t>;
//------------------------------------------------------- Attributs privés
	listenerQueue_t _listenerQueue;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées


};

//----------------------------------------- Types dépendants de <ActionHandler>
#include "ActionHandler.tpp"
#endif // ACTIONHANDLER_HPP

