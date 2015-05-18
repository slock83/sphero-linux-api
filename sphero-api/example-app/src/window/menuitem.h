/******************************************************************************
	MenuItem  - A console graphic menu item
							 -------------------
	started                : 14/05/2015
******************************************************************************/

#ifndef MENUITEM_H
#define MENUITEM_H


//-------------------------------------------------------- System includes
#include <string>

using namespace std;

//--------------------------------------------------------- Local includes
#include "ActionHandler.hpp"

//------------------------------------------------------------------ Types
typedef ActionHandler<> menuItemHandler_t;
typedef menuItemHandler_t::listener_t callback_menuItem_t;


//------------------------------------------------------ Class declaration
class MenuItem
{
	public:
		//----------------------------------------- Constructors/Destructor
		MenuItem(string _text);

		//-------------------------------------------------- Public methods

		/**
		 * @brief doAction : Called when a menu item is selected
		 */
		void doAction();

		/**
		 * @brief setAction : Add an action which will be called by doAction
		 * @param callback : The new action function
		 */
		void setAction(callback_menuItem_t callback);

		/**
		 * @brief itemText : Returns the item text
		 */
		string itemText();

	protected:
		string _text;
		menuItemHandler_t _actionHandler;
};

#endif // MENUITEM_H
