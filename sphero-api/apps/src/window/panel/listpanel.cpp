
#include <ncurses.h>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;



#include "listpanel.h"
#include "../panel.h"
#include "../keys.hpp"
#include "../../spheromanager.h"

ListPanel::ListPanel(int x, int y, int w, int h):
	Panel(x, y, w, h), _names(NULL), _nameLst(NULL), _menuWin(NULL),  _nbItems(0), _curIndex(0)
{
	sphM = SpheroManager::getManager();
	updateList(sphM->listSpheros());
}

ListPanel::~ListPanel()
{}

void ListPanel::drawPanel(int ch)
{
	initPanel();

	box(_panel, 0, 0);

	_menuWin = subwin(_panel, _height-2, _width-2, 1, 1);
	set_menu_win(_nameLst, _menuWin);

	switch(ch)
	{
		case KEY_KP8:
			if(menu_driver(_nameLst, REQ_UP_ITEM) == E_OK)
			{
				_curIndex--;
			}

			break;
		case KEY_KP2:
			if(menu_driver(_nameLst, REQ_DOWN_ITEM) == E_OK)
			{
				_curIndex++;
			}

			break;
		case KEY_KP6:
			sphM->selectSphero(_curIndex);
			updateSelected(_curIndex);
			break;
	}


	wrefresh(_menuWin);
	wrefresh(_panel);
}

void ListPanel::updateList(const vector<string>& newNames)
{
	string selected = "";

	if(_nbItems > 0)
		selected = spheroNames[_curIndex];

	_curIndex = 0;

	for(unsigned int i = 0; i < newNames.size(); ++i)
	{
		if(newNames[i] == selected)
		{
			_curIndex = i;
		}
	}

	spheroNames = newNames;


	if(_nameLst != NULL)
	{
		free_menu(_nameLst);
	}

	if(_names != NULL)
	{
		for(int i = 0; i < _nbItems; ++i)
			free_item(_names[i]);
		free(_names);
	}


	_nbItems = spheroNames.size();
	_names = (ITEM **)calloc(_nbItems + 1, sizeof(ITEM *));

	for(int i = 0; i < _nbItems; ++i)
	{
		stringstream ss(" ");
		ss << spheroNames[i];
		_names[i] = new_item(ss.str().c_str(), "");
	}
	_names[_nbItems] = (ITEM *)NULL;

	_nameLst = new_menu((ITEM **)_names);

	menu_opts_off(_nameLst, O_SHOWDESC);
	set_menu_mark(_nameLst, "");

	updateSelected(sphM->getSelectedIndex());

	for(int i = 0; i < _curIndex; ++i)
	{
		menu_driver(_nameLst, REQ_DOWN_ITEM);
	}

}

void ListPanel::updateSelected(int newIndex)
{
	if(newIndex == _selected)
		return;

		// Unmark as selected
	stringstream ssel(" ");
	ssel << spheroNames[_selected];
	free_item(_names[_selected]);
	_names[_selected] = new_item(ssel.str().c_str(), "");

		// Mark the new as selected
	stringstream snew("*");
	snew << spheroNames[newIndex];
	free_item(_names[newIndex]);
	_names[newIndex] = new_item(snew.str().c_str(), "");

	_selected = newIndex;
}
