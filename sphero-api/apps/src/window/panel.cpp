
#include "ncurses.h"

#include <iostream>
using namespace std;

#include "panel.h"

Panel::Panel(int x, int y, int w, int h):
	_startX(x), _startY(y), _width(w), _height(h), _panel(NULL)
{}

Panel::~Panel()
{
	delwin(_panel);
}


void Panel::drawPanel(int ch)
{
	initPanel();
	box(_panel, 0, 0);

	wrefresh(_panel);
	refresh();

}

void Panel::initPanel()
{
	delwin(_panel);
	_panel = newwin(_height, _width, _startY, _startX);
}

