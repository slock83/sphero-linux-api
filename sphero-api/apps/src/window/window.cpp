/******************************************************************************
	MenuItem  - The console graphic window manager
							 -------------------
	started                : 14/05/2015
******************************************************************************/

#include "ncurses.h"

#include "window.h"
#include "keys.hpp"

#include <iostream>
using namespace std;

Window::Window():
	_menuList(), _panelList(), _menus(NULL), _gMenu(NULL), _nbItems(0), _curItem(0), _hideBar(true)
{}

Window::~Window()
{
	for(Menu* m : _menuList)
		delete m;

	for(Panel* p: _panelList)
		delete p;
}

static void initScreen()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
}

void Window::showWindow()
{
	WINDOW *menubar, *menuw;
	WINDOW *test;
	initScreen();
	int ch = 0;
	initWindow();
	refresh();

	menubar=subwin(stdscr,1,80,0,0);
	menuw=newwin(10,80,1,0);

	while(1)
	{

		if(ch == 'q')
		{
			endwin();
			return;
		}

		werase(menuw);
		wrefresh(menuw);


		/* Refreshing panels */
		for(Panel *p : _panelList)
			p->drawPanel(ch);

		/* Refreshing menu */
		drawMenuBar(ch, menubar);

		if(menuw != NULL)
			delwin(menuw);
		menuw = NULL;
		if(!_hideBar)
		{
			int w, h;

			_menuList[_curItem]->getSize(h, w);
			menuw = newwin(h, w+1, 1, _curItem * _menuSize);
			_menuList[_curItem]->showMenu(ch, menuw);
			wrefresh(menuw);
		}

		wrefresh(menubar);


		ch = getch();
	}
}

void Window::addMenu(Menu *m)
{
	_menuList.push_back(m);
}

void Window::addPanel(Panel *p)
{
	_panelList.push_back(p);
}

void Window::drawMenuBar(int ch, WINDOW *w)
{
	set_menu_win(_gMenu, w);
	switch(ch)
	{
		case KEY_LEFT:
			if(menu_driver(_gMenu, REQ_LEFT_ITEM) == E_OK)
			{

				if(_hideBar)
				{
					menu_driver(_gMenu, REQ_RIGHT_ITEM);
				}

				_menuList[_curItem]->initMenu();

				if(!_hideBar)
					_curItem--;

				_hideBar = false;
			}
			else
				_hideBar = true;

			break;
		case KEY_RIGHT:
			if(menu_driver(_gMenu, REQ_RIGHT_ITEM) == E_OK)
			{
				if(_hideBar)
				{
					menu_driver(_gMenu, REQ_LEFT_ITEM);
				}

				_menuList[_curItem]->initMenu();

				if(!_hideBar)
					_curItem++;

				_hideBar = false;
			}
			else
				_hideBar = true;
			break;
		case KEY_DOWN:
			if(_hideBar)
			{
				_hideBar = false;
				_menuList[_curItem]->initMenu();
			}
			break;
		case KEY_ESCAPE:
			_hideBar = true;
			break;
	}

	post_menu(_gMenu);
}

void Window::initWindow()
{
	_curItem = 0;

	/* Handling multiple calls */

	if(_gMenu != NULL)
	{
		free_menu(_gMenu);
	}

	if(_menus != NULL)
	{
		for(int i = 0; i < _nbItems; ++i)
			free_item(_menus[i]);
		free(_menus);
	}

	/* Init (Creation of the ncurses menu) */
	_nbItems = _menuList.size();
	_menuSize = 0;
	_menus = (ITEM **)calloc(_nbItems + 1, sizeof(ITEM *));

	for(int i = 0; i < _nbItems; ++i)
	{
		int size = _menuList[i]->getName().size();
		if(_menuSize < size)
			_menuSize = size;

		_menus[i] = new_item(_menuList[i]->getName().c_str(), "");
	}
	_menus[_nbItems] = (ITEM *)NULL;

	_gMenu = new_menu((ITEM **)_menus);


	menu_opts_off(_gMenu, O_SHOWDESC);

	set_menu_format(_gMenu, 1, 16);
	set_menu_mark(_gMenu, "");


}

