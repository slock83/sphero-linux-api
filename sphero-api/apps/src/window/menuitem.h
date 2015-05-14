#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

using namespace std;

#include "ActionHandler.hpp"

typedef ActionHandler<> menuItemHandler_t;
typedef menuItemHandler_t::listener_t callback_menuItem_t;


class MenuItem
{
	public:
		MenuItem(string text);

		void doAction();
		void setAction(callback_menuItem_t callback);
		string itemText();

	protected:
		string text;
		menuItemHandler_t _actionHandler;
};

#endif // MENUITEM_H
