/******************************************************************************
	MenuItem  - The console graphic window manager
							 -------------------
	started                : 14/05/2015
******************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

//-------------------------------------------------------- System includes

#include <ncurses.h>
#include <vector>

using namespace std;


//--------------------------------------------------------- Local includes

#include "ncmenu.h"
#include "panel.h"


//------------------------------------------------------ Class declaration
class Window
{
	public:
		//----------------------------------------- Constructors/Destructor

		Window();

		virtual ~Window();

		//-------------------------------------------------- Public methods

		/**
		 * @brief showWindow : Starts ncurses and shows the window
		 */
		void showWindow();

		/**
		 * @brief addMenu : Adds a new menu to the window
		 * @param m : A pointer to the new menu
		 */
		void addMenu(Menu *m);

		/**
		 * @brief addPanel : Adds a new panel to the window
		 * @param p : A pointer to the new panel
		 */
		void addPanel(Panel *p);

	protected:
		vector<Menu*> _menuList;
		vector<Panel*> _panelList;

		ITEM** _menus;
		MENU* _gMenu;

		int _nbItems;
		int _menuSize;
		int _hideBar;

		int _curItem;

		//----------------------------------------------- Protected methods

		void drawMenuBar(int ch, WINDOW *w);

		void initWindow();

};

#endif // WINDOW_H
