#ifndef PANEL_H
#define PANEL_H

#include <ncurses.h>

class Panel
{
	public:
		Panel(int x, int y, int w, int h);
		virtual ~Panel();

		virtual void drawPanel(int ch);

	protected:
		int _startX, _startY;
		int _width, _height;

		WINDOW* _panel;

		void initPanel();

};

#endif // PANEL_H
