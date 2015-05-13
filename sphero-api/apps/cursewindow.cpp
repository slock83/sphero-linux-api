#include "cursewindow.h"

#include "ncurses.h"

CurseWindow::CurseWindow()
{}

static void initScreen()
{
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
}



void CurseWindow::showWindow()
{
	initScreen();
	int col, row;

}

