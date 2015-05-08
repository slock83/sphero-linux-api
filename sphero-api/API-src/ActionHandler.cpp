/*************************************************************************
	ActionHandler  - Generic template to handle diverse actions
                             -------------------
    début                : ven. 08 mai 2015
*************************************************************************/

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "ActionHandler.hpp"

//------------------------------------------------ Constructors/Destructor

/**
 * @brief ActionHandler : Constructor
 */
ActionHandler::ActionHandler():_listenerQueue()
{}

ActionHandler::~ActionHandler ( )
{}

//--------------------------------------------------------- Public methods

template<typename T>
/**
 * @brief reportAction : Reports the ocurred action to actionHandler.
 *				All listeners are then notified.
 * @param action : A pointer to the action informations data structure
 */
void ActionHandler::reportAction(T* action)
{
	std::queue<listener<T> const>::iterator it;
	for(it = _listenerQueue.begin() ; it != _listenerQueue.end() ; it++)
	{
		*it(action);
	}
}


template<typename T>
/**
 * @brief addActionListener : Registers a new listener
 * @param : listener : The new listener which will be registered
 */
void ActionHandler::addActionListener(listener<T> const listener)
{
	_listenerQueue.push(listener);
}


template<typename T>
/**
 * @brief clearListener : Unregisters all listeners
 */
void clearListener()
{
	std::queue<listener<T> const> empty;
	std::swap(_listenerQueue, empty);

}

