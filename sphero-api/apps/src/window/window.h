/******************************************************************************
	MenuItem  - The console graphic window manager
							 -------------------
	started                : 14/05/2015
******************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <ncurses.h>
using namespace std;

#include "ncmenu.h"
#include "panel.h"

class Window
{
	public:
		Window();
		virtual ~Window();

		void showWindow();

		void addMenu(Menu *m);
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

		void drawMenuBar(int ch, WINDOW *w);
		void initWindow();

};

#endif // WINDOW_H
