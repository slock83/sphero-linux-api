/******************************************************************************
	ActionHandler  - Generic template to handle diverse actions
                             -------------------
	début                : ven. 08 mai 2015
******************************************************************************/

#ifndef ( ACTIONHANDLER_HPP )
#define ACTIONHANDLER_HPP

//-------------------------------------------------------- System includes
#include <queue>
#include <functional>
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 


/**
 * T : Data structure type which will be communicated to all listeners
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

#endif // ACTIONHANDLER_HPP
