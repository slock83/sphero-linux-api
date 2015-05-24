/*************************************************************************
	SnesController -- Interactive mode controller for sphero
							 -------------------
	start                : 24/05/2015
*************************************************************************/

#ifndef SNESCONTROLLER_H
#define SNESCONTROLLER_H

//-------------------------------------------------------- System includes

#include <stddef.h>
#include <unistd.h>
#include "sphero/Sphero.hpp"


//--------------------------------------------------------- Local includes
#include "Keys.hpp"
#include "snescontroller.h"


//------------------------------------------------------- Class definition
class SnesController
{
	public:
		//--------------------------------------- Constructors/Destructor
		SnesController();

		virtual ~SnesController();


		//------------------------------------------------ Public methods

		/**
		 * @brief startJoystickMode : starts the interactive mode
		 *									(blocks until it is exited)
		 * @param s : The sphero to control
		 */
		void startJoystickMode(Sphero *s);

	private:
		struct js_event {
				uint32_t time;     /* event timestamp in milliseconds */
				int16_t value;    /* value */
				uint8_t type;      /* event type */
				uint8_t number;    /* axis/button number */
			};

		struct keys
		{
			int a;
			int b;
			int x;
			int y;
			int lb;
			int rb;
			int start;
			int select;
			int horiz;
			int vert;
		};

		/* Sphero which will be controlled */
		Sphero *s;

		//Joystick file descriptor
		int joy;
		struct keys keys;


		bool isBackLedEnabled;
		bool exit;
		int speed;
		int lastDrivingAngle;

		bool isConnected();
		//void settingsMode();
		void joyLoop();
		void updateKeys();
		void initKeys();

		int stateDecode(struct js_event e);

		void help();

		//----------------------------------------------- Private classes
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
					t.c_lflag &= ~ICANON; //disable canonical mode
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

#endif // SNESCONTROLLER_H
