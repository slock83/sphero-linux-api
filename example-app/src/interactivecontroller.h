/*************************************************************************
	InteractiveController -- Interactive mode controller for sphero
							 -------------------
	start                : 13/05/2015
*************************************************************************/

#ifndef INTERACTIVECONTROLLER_H
#define INTERACTIVECONTROLLER_H

//-------------------------------------------------------- System includes

#include <stddef.h>
#include <unistd.h>
#include "sphero/Sphero.hpp"
#include "JoystickAdaptor.h"


//--------------------------------------------------------- Local includes
#include "Keys.hpp"


//------------------------------------------------------- Class definition
class InteractiveController
{
	public:
		//--------------------------------------- Constructors/Destructor
		InteractiveController();

		virtual ~InteractiveController();


		//------------------------------------------------ Public methods

		/**
		 * @brief startInteractiveMode : starts the interactive mode
		 *									(blocks until it is exited)
		 * @param s : The sphero to control
		 */
		void startInteractiveMode(Sphero *s);

	private:

		/* Sphero which will be controlled */
		Sphero *s;
		mode commandMode;
		JoystickAdaptor* ja;
		JoystickEvent lastEvent;

		bool isBackLedEnabled;
		uint16_t lastAngle;

		int dead;

		bool isConnected();

		void handleKeysClassic(int input, timeval &lastInput);
		void handleKeysCalibrate(int input, timeval &lastInput);
		void handleKeysJoystick(timeval &lastInput);

		void changeMode(mode newMode);

		void classicHelp();
		void calibrateHelp();
		void joystickHelp();

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
