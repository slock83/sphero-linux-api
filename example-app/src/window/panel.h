/******************************************************************************
	MenuItem  - A console graphic panel
							 -------------------
	started                : 14/05/2015
******************************************************************************/

#ifndef PANEL_H
#define PANEL_H

//-------------------------------------------------------- System includes
#include <ncurses.h>


//------------------------------------------------------ Class declaration
class Panel
{
	public:
		//----------------------------------------- Constructors/Destructor
		/**
		 * @brief Panel : Constructor
		 * @param x : The up/left corner X position
		 * @param y : The up/left corner Y position
		 * @param w : The panel width
		 * @param h : The panel height
		 */
		Panel(int x, int y, int w, int h);

		virtual ~Panel();

		//-------------------------------------------------- Public methods

		/**
		 * @brief drawPanel : Draws the panel on console
		 * @param ch : The last pressed key code
		 */
		virtual void drawPanel(int ch);

	protected:
		int _startX, _startY;
		int _width, _height;

		WINDOW* _panel;

		//----------------------------------------------- Protected methods

		/**
		 * @brief initPanel : Initialization of nCurses parameters. Is called by drawPanel
		 */
		void initPanel();

};

#endif // PANEL_H
