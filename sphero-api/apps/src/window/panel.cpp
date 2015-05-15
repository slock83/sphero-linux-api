/******************************************************************************
	MenuItem  - A console graphic panel
							 -------------------
	started                : 14/05/2015
******************************************************************************/


//-------------------------------------------------------- System includes
#include "ncurses.h"


//--------------------------------------------------------- Local includes
#include "panel.h"


//------------------------------------------------ Constructors/Destructor

/**
 * @brief Panel : Constructor
 * @param x : The up/left corner X position
 * @param y : The up/left corner Y position
 * @param w : The panel width
 * @param h : The panel height
 */
Panel::Panel(int x, int y, int w, int h):
	_startX(x), _startY(y), _width(w), _height(h), _panel(NULL)
{}

Panel::~Panel()
{
	delwin(_panel);
}

//--------------------------------------------------------- Public methods

/**
 * @brief drawPanel : Draws the panel on console
 * @param ch : The last pressed key code
 */
void Panel::drawPanel(int ch)
{
	initPanel();
	box(_panel, 0, 0);

	wrefresh(_panel);
	refresh();

}


//----------------------------------------------------- Protected methods

/**
 * @brief initPanel : Initialization of nCurses parameters. Is called by drawPanel
 */
void Panel::initPanel()
{
	delwin(_panel);
	_panel = newwin(_height, _width, _startY, _startX);
}

