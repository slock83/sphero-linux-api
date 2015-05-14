#ifndef MENU_H
#define MENU_H

#include <vector>
#include <menu.h>

using namespace std;


#include "menuitem.h"

//TODO : memleaks...
class Menu
{
	public:
		Menu(string name);
		virtual ~Menu();

		void addItem(MenuItem *m);
		void removeItem(int index);

		void initMenu();// TODO : le passer en privé + ami avec window?
						// Ou alors: appel à chaque ajout/suppr d'un item
		void showMenu(int ch, WINDOW *w);
		void hideMenu(int ch, WINDOW *w);

		string getName();

		void getSize(int& height, int& width);

	protected:
		string _menuName;
		vector<MenuItem*> _itemList;

		ITEM** _my_items;
		MENU* _my_menu;

		int _nbItems;
		int _curItem;
};

#endif // MENU_H
