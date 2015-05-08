/******************************************************************************
	ActionHandler  - Generic template to handle diverse actions
                             -------------------
	début                : ven. 08 mai 2015
******************************************************************************/

#ifndef ( ACTIONHANDLER_HPP )
#define ACTIONHANDLER_HPP

//-------------------------------------------------------- System includes
#include <queue>

//------------------------------------------------------------------ Types 
template<typename T>
typedef void (listener<T>*)(T);


/**
 * T : Data structure type which will be communicated to all listeners
 */
template<typename T>
class ActionHandler 
{
	public :
		//------------------------------------------------- Operators overload
			//No sense
		ActionHandler& operator=(const ActionHandler&) = delete;

		//-------------------------------------------- Constructors/Destructor
			//No sense
		ActionHandler(const ActionHandler&) = delete;

		/**
		 * @brief ActionHandler : Constructor
		 */
		ActionHandler();

		virtual ~ActionHandler();

		//----------------------------------------------------- Public methods
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

	private:
		std::queue<listener<T> const> _listenerQueue;

};

#endif // ACTIONHANDLER_HPP
