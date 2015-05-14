/******************************************************************************
	ActionHandler  - Generic template to handle diverse actions
                             -------------------
	started                : 08/05/2015
******************************************************************************/

#ifndef ACTIONHANDLER_HPP
#define ACTIONHANDLER_HPP

//-------------------------------------------------------- System includes
#include <list>
#include <functional>


//------------------------------------------------------- Class definition
/**
 * T : Data structure type which will be communicated to all listeners
 */
template<typename ...T>
class ActionHandler 
{
	public :
		//---------------------------------------------------- Local types
		using listener_t = std::function<void(T...)>;


		//--------------------------------------------- Operators overload
			//No sense
		ActionHandler& operator=(const ActionHandler&) = delete;


		//---------------------------------------- Constructors/Destructor
			//No sense
		ActionHandler(const ActionHandler&) = delete;

		/**
		 * @brief ActionHandler : Constructor
		 */
		ActionHandler();

		virtual ~ActionHandler();


		//------------------------------------------------- Public methods

		/**
		 * @brief reportAction : Reports the ocurred actions to actionHandler.
		 *				All listeners are then notified.
		 * @param action : A pointer to the action informations data structure
		 */
		void reportAction(T... action);


		/**
		 * @brief addActionListener : Registers a new listener
		 * @param : listener : The new listener which will be registered
		 */
		void addActionListener(listener_t listener);


		/**
		 * @brief clearListener : Unregisters all listeners
		 */
		void clearListener();

	private:
		//-------------------------------------------------- Private types
		using listenerList_t = std::list<listener_t>;

		//--------------------------------------------- Private attributes
		listenerList_t _listenerList;
};

#include "ActionHandler.tpp"

#endif // ACTIONHANDLER_HPP
