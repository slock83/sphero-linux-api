/*************************************************************************
	ActionHandler  - Generic template to handle diverse actions
                             -------------------
    début                : ven. 08 mai 2015
*************************************************************************/

//--------------------------------------------------------- Local includes
#include "ActionHandler.hpp"

//------------------------------------------------ Constructors/Destructor

/**
 * @brief ActionHandler : Constructor
 */
template<typename ...T>
ActionHandler<T...>::ActionHandler():_listenerQueue()
{}


template<typename ...T>
ActionHandler<T...>::~ActionHandler ( )
{}


//--------------------------------------------------------- Public methods

/**
 * @brief reportAction : Reports the ocurred actions to actionHandler.
 *				All listeners are then notified.
 * @param action : A pointer to the action informations data structure
 */
template<typename ...T>
void ActionHandler<T...>::reportAction(T... action)
{
	std::queue<listener<T> const>::iterator it;
	for(it = _listenerQueue.begin() ; it != _listenerQueue.end() ; it++)
	{
		*it(action);
	}
}


/**
 * @brief addActionListener : Registers a new listener
 * @param : listener : The new listener which will be registered
 */
template<typename ...T>
void ActionHandler<T...>::addActionListener(listener_t listener)
{
	_listenerQueue.push(listener);
}


/**
 * @brief clearListener : Unregisters all listeners
 */
template<typename ...T>
void ActionHandler<T...>::clearListener()
{
	std::queue<listener<T> const> empty;
	std::swap(_listenerQueue, empty);

}


