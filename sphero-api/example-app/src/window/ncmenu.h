/******************************************************************************
	Menu  - A console graphic menu
							 -------------------
	started                : 14/05/2015
******************************************************************************/

#ifndef MENU_H
#define MENU_H

//-------------------------------------------------------- System includes
#include <vector>
#include <string>
#include <menu.h>

using namespace std;


//--------------------------------------------------------- Local includes

#include "menuitem.h"


//------------------------------------------------------ Class declaration
class Menu //TODO : memleaks...
{
	public:
		//----------------------------------------- Constructors/Destructor
		Menu(string name);

		virtual ~Menu();

		//-------------------------------------------------- Public methods

		/**
		 * @brief addItem : Adds an item to the menu
		 * @param m : The menuItem to add
		 */
		void addItem(MenuItem *m);


		/**
		 * @brief removeItem : Removes an item from the menu
		 * @param index : The index of the item to remove
		 */
		void removeItem(unsigned int index);


		/**
		 * @brief initMenu : Initializes the menu (ncurses objects)
		 */
		void initMenu();


		/**
		 * @brief showMenu : Shows the menu and performs base actions on it
		 * @param ch : The last keyCode performed
		 * @param w : The window wherethe menu will be showed
		 */
		void showMenu(int ch, WINDOW *w);


		/**
		 * @brief getName : Returns the menu name
		 */
		string getName();


		/**
		 * @brief getSize : Computes the menu dimensions (to create a window perfectly fitting)
		 * @param height : Reference, the menu height will be placed here
		 * @param width : Reference, the menu width will be placed here
		 */
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
