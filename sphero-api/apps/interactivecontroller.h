#ifndef INTERACTIVECONTROLLER_H
#define INTERACTIVECONTROLLER_H

#include "../API-src/Sphero.hpp"

class InteractiveController
{
	public:
		InteractiveController();

		void startInteractiveMode(Sphero *s);

	private:

		/* Sphero which will be controlled */
		Sphero *s;

		bool isConnected();

		class BufferToggle
		{
			private:
				struct termios t;
				struct termios o;

			public:

				/*
				 * Disables buffered input
				 */
				void off(void)
				{
					tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
					o = t;
					t.c_lflag &= ~ICANON; //disable canonical mmode
					t.c_lflag &= ~ECHO; //disable echoing
					t.c_lflag &= ~ISIG;
					t.c_cc[VMIN] = 0;
					t.c_cc[VTIME] = 0;
					tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings

				}

				/*
				 * Enables buffered input
				 * MUST be run AFTER off
				 */
				void on(void)
				{
					tcsetattr(STDIN_FILENO, TCSANOW, &o); //Apply the new settings
				}
		};
};

#endif // INTERACTIVECONTROLLER_H
