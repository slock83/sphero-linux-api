#ifndef LISTPANEL_H
#define LISTPANEL_H

#include <ncurses.h>
#include <menu.h>
#include <vector>
#include <string>

using namespace std;

#include "../panel.h"
#include "../../spheromanager.h"

class ListPanel : public Panel
{
	public:
		ListPanel(int x, int y, int w, int h);
		virtual ~ListPanel();

		virtual void drawPanel(int ch);

		void updateList(const vector<string>& newNames);
		void updateSelected(int newIndex);

	protected:
		SpheroManager *sphM;

		vector<string> spheroNames;

		ITEM** _names;
		MENU* _nameLst;
		WINDOW* _menuWin;

		int _nbItems;
		int _curIndex;
		int _selected;
};

#endif // LISTPANEL_H
