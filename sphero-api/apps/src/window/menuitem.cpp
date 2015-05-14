#include "menuitem.h"

MenuItem::MenuItem(string text) : text(text)
{}

void MenuItem::doAction()
{
	_actionHandler.reportAction();
}

void MenuItem::setAction(callback_menuItem_t callback)
{
	_actionHandler.addActionListener(callback);
}

string MenuItem::itemText()
{
	return text;
}

