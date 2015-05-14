#include "cursewindow.h"
#include "Keys.hpp"
#include "ncurses.h"


CurseWindow::CurseWindow()
{}

static void initScreen()
{
	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
						 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
}

//Currently heading: //18 chars


static void drawRightPanel(int x, int y, int w, int h)
{
	WINDOW *right_panel;
	right_panel = newwin(h, w, y, x);

	box(right_panel, 0 , 0);

	mvwprintw(right_panel, 1, 4, "Sphero list:");
	/*mvwprintw(right_panel, 1, 1, "Heading: 50 deg");
	mvwprintw(right_panel, 2, 1, "Speed: 100 km/h");
	mvwprintw(right_panel, 3, 1, "Color: #0a2f64");*/
	//mvwprintw(right_panel, 2, 1, "50 deg");


	wrefresh(right_panel);

	delwin(right_panel);
}

void CurseWindow::showWindow()
{
	int ch;
	int row,col;
	initscr();			/* Start curses mode 		*/
	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on
						 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();

	getmaxyx(stdscr,row,col);


	do
	{
		drawRightPanel(col - 20, 0, 20, row);
		refresh();

	}while((ch = getch()) != global::_KEY_QUIT);


	endwin();
}
