/******************************************************************************
	MenuItem  - A console graphic menu item
							 -------------------
	started                : 14/05/2015
******************************************************************************/

//-------------------------------------------------------- System includes
#include <string>

using namespace std;


//--------------------------------------------------------- Local includes
#include "menuitem.h"


//------------------------------------------------ Constructors/Destructor
MenuItem::MenuItem(string text) : _text(text)
{}


//--------------------------------------------------------- Public methods

/**
 * @brief doAction : Called when a menu item is selected
 */
void MenuItem::doAction()
{
	_actionHandler.reportAction();
}


/**
 * @brief setAction : Add an action which will be called by doAction
 * @param callback : The new action function
 */
void MenuItem::setAction(callback_menuItem_t callback)
{
	_actionHandler.addActionListener(callback);
}


/**
 * @brief itemText : Returns the item text
 */
string MenuItem::itemText()
{
	return _text;
}

