/*************************************************************************
	InteractiveController -- Interactive mode controller for sphero
							 -------------------
	start                : 13/05/2015
*************************************************************************/


//-------------------------------------------------------- System includes
#include <iostream>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>

#include "ncurses.h"

#include "sphero/Sphero.hpp"

using namespace std;


//--------------------------------------------------------- Local includes
#include "interactivecontroller.h"
#include "Keys.hpp"


//-------------------------------------------------------------- Constants
static const uint8_t _SPEED = 128;
static const uint8_t _MAX_LIGHT = 255;

//------------------------------------------------ Constructors/Destructor
InteractiveController::InteractiveController() : isBackLedEnabled(false), commandMode(mode::CLASSIC)
{}

InteractiveController::~InteractiveController()
{}



//--------------------------------------------------------- Public methods

/**
 * @brief startInteractiveMode : starts the interactive mode
 *									(blocks until it is exited)
 * @param s : The sphero to control
 */
void InteractiveController::startInteractiveMode(Sphero *s)
{
	this->s = s;
	if(!isConnected()) return;



	cout << "************************************" << endl;
	cout << "*    welcome to interactive mode   *" <<endl;
	classicHelp();

	BufferToggle bt;
	bt.off();
	int input;

	timeval lastInput, now;
	double elapsedTime;

	// start timer
	gettimeofday(&lastInput, NULL);
	do
	{
		input = getchar();
		switch (commandMode)
		{
			case mode::CLASSIC:
				handleKeysClassic(input, lastInput);
				break;
			case mode::CALIBRATE:
				handleKeysCalibrate(input, lastInput);
				break;
		}

#ifdef MAP
		if(input != -1)
			cout << "You pressed key ID: " << input << endl;
#endif
		gettimeofday(&now, NULL);


		elapsedTime = (now.tv_sec - lastInput.tv_sec) * 1000.0;      // sec to ms
		elapsedTime += (now.tv_usec - lastInput.tv_usec) / 1000.0;
		//cout << elapsedTime << endl;
		if(elapsedTime >= 120)
			s->roll((uint8_t) 0 % 256, (uint16_t) lastAngle % 0x10000);
		usleep(8000);
	}while(input != global::_KEY_QUIT);

	bt.on();
}



//-------------------------------------------------------- Private methods
bool InteractiveController::isConnected()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return false;
	}
	return true;
}


void InteractiveController::handleKeysClassic(int input, timeval &lastInput)
{
	if(input == classic::_KEY_FORWARD )
	{
		s->roll((uint8_t)_SPEED % 256,(uint16_t) 0 % 0x10000,1);
		lastAngle = 0;
	}
	else if(input == classic::_KEY_BACKWARD )
	{
		s->roll((uint8_t)_SPEED % 256,(uint16_t) 180 % 0x10000,1);
		lastAngle = 180;
	}
	else if(input == classic::_KEY_RIGHT )
	{
		s->roll((uint8_t)_SPEED % 256,(uint16_t) 90 % 0x10000,1);
		lastAngle = 90;
	}
	else if(input == classic::_KEY_LEFT )
	{
		s->roll((uint8_t) _SPEED % 256, (uint16_t) 270 % 0x10000, 1);
		lastAngle = 270;
	}
	else if(input == classic::_KEY_BACKLIGHT )
	{
		if(isBackLedEnabled)
			s->setBackLedOutput(0);
		else
			s->setBackLedOutput(_MAX_LIGHT);

		isBackLedEnabled = !isBackLedEnabled;
	}
	else if(input == classic::_KEY_MODE_CALIBRATE)
	{
		changeMode(mode::CALIBRATE);

		s->setBackLedOutput(_MAX_LIGHT);
		isBackLedEnabled = true;

		s->roll(0, 0);
		lastAngle = 0;
	}
	else
		return;

	gettimeofday(&lastInput, NULL);
}



void InteractiveController::handleKeysCalibrate(int input, timeval& lastInput)
{
	if(input == calibrate::_KEY_LEFT_2)
		lastAngle += 2;
	else if(input == calibrate::_KEY_LEFT_10)
		lastAngle += 10;
	else if(input == calibrate::_KEY_RIGHT_2)
		lastAngle -= 2;
	else if(input == calibrate::_KEY_RIGHT_10)
		lastAngle -= 10;
	else if(input == calibrate::_KEY_VALIDATE)
	{
		s->setHeading(0);
		changeMode(mode::CLASSIC);

		s->setBackLedOutput(0);
		isBackLedEnabled = false;

		gettimeofday(&lastInput, NULL);
		return;
	}
	else if(input == calibrate::_KEY_RETURN)
	{
		changeMode(mode::CLASSIC);
		s->setBackLedOutput(0);
		isBackLedEnabled = false;

		gettimeofday(&lastInput, NULL);
		return;
	}
	else
		return;

	if(lastAngle >= 360)
		lastAngle -= 360;

	if(lastAngle <= 0)
		lastAngle += 360;

	s->roll(0, lastAngle);
	gettimeofday(&lastInput, NULL);
}

void InteractiveController::changeMode(mode newMode)
{
	if(commandMode == newMode)
		return;
	commandMode = newMode;

	switch (commandMode) {
		case mode::CLASSIC:
			classicHelp();
			break;
		case mode::CALIBRATE:
			calibrateHelp();
			break;
	}
}

void InteractiveController::classicHelp()
{

	cout << "************************************" << endl;
	cout << "****** Classic mode commands *******" << endl;
	cout << "************************************" << endl;
	cout << "*          press q to quit         *" << endl;
	cout << "*                                  *" << endl;
	cout << "*         arrow keys to move       *" << endl;
	cout << "*   b to enable/disable backled    *" << endl;
	cout << "*    c to enter calibrate mode     *" << endl;
	cout << "*                                  *" << endl;
	cout << "************************************" << endl;
}

void InteractiveController::calibrateHelp()
{

	cout << "************************************" << endl;
	cout << "***** Calibrate mode commands ******" << endl;
	cout << "************************************" << endl;
	cout << "*          press q to quit         *" << endl;
	cout << "*                                  *" << endl;
	cout << "*     press r to turn left(2°)     *" << endl;
	cout << "*     press e to turn left(10°)    *" << endl;
	cout << "*     press t to turn right(2°)    *" << endl;
	cout << "*     press y to turn right(10°)   *" << endl;
	cout << "*                                  *" << endl;
	cout << "*        press v to validate       *" << endl;
	cout << "*         press b to return        *" << endl;
	cout << "************************************" << endl;
}
