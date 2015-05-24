/*************************************************************************
	SnesController -- Interactive mode controller for sphero
							 -------------------
	start                : 24/05/2015
 *************************************************************************/


//-------------------------------------------------------- System includes
#include <iostream>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>

#include "ncurses.h"

#include "sphero/Sphero.hpp"

using namespace std;


//--------------------------------------------------------- Local includes
#include "snescontroller.h"
#include "Keys.hpp"


//-------------------------------------------------------------- Constants
static const uint8_t _SPEED = 128;
static const uint8_t _MAX_LIGHT = 255;
static const int LATENCY = 50000;

//------------------------------------------------ Constructors/Destructor
SnesController::SnesController() : isBackLedEnabled(false), exit(false)
{}

SnesController::~SnesController()
{}



//--------------------------------------------------------- Public methods

/**
 * @brief startInteractiveMode : starts the interactive mode
 *									(blocks until it is exited)
 * @param s : The sphero to control
 */
void SnesController::startJoystickMode(Sphero *s)
{
	this->s = s;
	if(!isConnected()) return;
	joy = open ("/dev/input/js0", O_RDONLY | O_NONBLOCK);
	if (joy < 0)
	{
		cout << "there was an error opening the joystick, is it plugged ?" << endl;
		return;
	}
	cout << "************************************" << endl;
	cout << "*     welcome to joystick mode     *" <<endl;
	help();
	exit = false;



	BufferToggle bt;
	bt.off();
	joyLoop();

	bt.on();
}



//-------------------------------------------------------- Private methods
bool SnesController::isConnected()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return false;
	}
	return true;
}


void SnesController::joyLoop()
{
	while(!exit)
	{
		updateKeys();

		if(keys.x == 2)
		{
			if(isBackLedEnabled)
			{
				s->setBackLedOutput(0);
				keys.x = 1; //so we only catch rising edge
				isBackLedEnabled = false;
			}
			else if(!isBackLedEnabled)
			{
				s->setBackLedOutput(255);
				keys.x = 1; //so we only catch rising edge
				isBackLedEnabled = true;
			}


		}

		//reorient
		if(keys.lb || keys.rb)
		{
			double lastAngle = 0;
			while(keys.lb || keys.rb)
			{
				updateKeys();
				if(keys.lb && !keys.rb)
				{
					//fast mode
					if(keys.a)
					{
						lastAngle += 1;
					}
					else
					{
						lastAngle +=0.2;
					}
				}
				else if (keys.rb && !keys.lb)
				{
					//fast mode
					if(keys.a)
					{
						lastAngle -= 1;
					}
					else
					{
						lastAngle -=0.2;
					}
				}
				if(lastAngle >= 360)
					lastAngle -= 360;

				if(lastAngle <= 0)
					lastAngle += 360;

				s->roll(0, (int) lastAngle);

			}
			s->setHeading(0);

		}
		else if(keys.start ==2)
		{
			s->roll(0,0);
			keys.start = 1;
			cout << "menu" << endl;
			cout << "X : go back to console" << endl;
			cout << "B : drive !" << endl;
			cout << "L/R to change driving speed" << endl;
			bool menu = true;
			while ( menu && !exit )
			{
				updateKeys();
				if ( keys.start == 2 )
				{
					keys.start = 1;
					menu = false;
				}
				else if ( keys.x ) exit = true;
				else if ( keys.b ) menu = false;
				else if ( keys.lb && !keys.rb )
				{
					if(keys.a) speed -=10;
					else speed --;
					if ( speed<0 ) speed = 0;
					cout << "speed = " << speed << endl;
					usleep(100000);
				}
				else if (keys.rb && !keys.lb)
				{
					if(keys.a) speed +=10;
					else speed ++;
					if ( speed>255 ) speed = 255;
					cout << "speed = " << speed << endl;
					usleep(100000);
				}
			}
			cout << "resuming drive" << endl;

		}
		else if ((keys.horiz != 0) || (keys.vert != 0))
		{
			if(keys.a)
			{
				if (keys.vert <0)
				{
					if (keys.horiz >0)
					{
						s->roll(speed*2, 45);
						lastDrivingAngle = 45;
					}
					else if (keys.horiz < 0)
						{
						s->roll(speed*2, 315);
						lastDrivingAngle = 315;
						}
					else
						{
						s->roll(speed*2, 0);
						lastDrivingAngle = 0;
						}
				}
				else if (keys.vert >0)
				{
					if (keys.horiz >0)
						{
						s->roll(speed*2, 135);
						lastDrivingAngle = 135;
						}
					else if (keys.horiz < 0)
						{
						s->roll(speed*2, 225);
						lastDrivingAngle = 225;
						}
					else
						{
						s->roll(speed*2, 180);
						lastDrivingAngle = 180;
						}
				}
				else if (keys.horiz < 0)
					{
					s->roll(speed*2, 270);
					lastDrivingAngle = 270;
					}
				else if (keys.horiz > 0)
					{
					s->roll(speed*2, 90);
					lastDrivingAngle = 90;
					}
			}
			else
			{
				if (keys.vert <0)
				{
					if (keys.horiz >0)
						{
						s->roll(speed, 45);
						lastDrivingAngle = 45;
						}
					else if (keys.horiz < 0)
						{
						s->roll(speed, 315);
						lastDrivingAngle = 315;
						}
					else
						{
						s->roll(speed, 0);
						lastDrivingAngle = 0;
						}
				}
				else if (keys.vert >0)
				{
					if (keys.horiz >0)
						{
						s->roll(speed, 135);
						lastDrivingAngle = 135;
						}
					else if (keys.horiz < 0)
						{
						s->roll(speed, 225);
						lastDrivingAngle = 225;
						}
					else
						{
						s->roll(speed, 180);
						lastDrivingAngle = 180;
						}
				}
				else if (keys.horiz < 0)
					{
					s->roll(speed, 270);
					lastDrivingAngle = 270;
					}
				else if (keys.horiz > 0)
					{
					s->roll(speed, 90);
					lastDrivingAngle = 90;
					}
			}

		}
		else
		{
			s->roll(0,lastDrivingAngle);
		}

	}

}

void SnesController::updateKeys()
{
	struct js_event e;
	if(read (joy, &e, sizeof(e))<0) return;
	if(e.type & snesPad::EVENT_INIT)
	{
		//ignore this
	}
	else
	{
		if(e.type == snesPad::EVENT_AXIS)
		{
			if(e.number == snesPad::AXIS_HORIZ)
				keys.horiz = (int) e.value;
			if(e.number == snesPad::AXIS_VERT)
			{
				keys.vert = (int) e.value;
			}
		}
		else
		{
			if(e.number == snesPad::KEY_A)
			{
				keys.a = stateDecode(e);
			}
			if(e.number == snesPad::KEY_B)
			{
				keys.b = stateDecode(e);
			}
			if(e.number == snesPad::KEY_X)
			{
				keys.x = stateDecode(e);
			}
			if(e.number == snesPad::KEY_Y)
			{
				keys.y = stateDecode(e);
			}
			if(e.number == snesPad::KEY_LB)
			{
				keys.lb = stateDecode(e);
			}
			if(e.number == snesPad::KEY_RB)
			{
				keys.rb = stateDecode(e);
			}
			if(e.number == snesPad::KEY_START)
			{
				keys.start = stateDecode(e);
			}
			if(e.number == snesPad::KEY_SEL)
			{
				keys.select = stateDecode(e);
			}
		}
		usleep(LATENCY);
#ifdef MAP
		cout << hex << (int) e.number << endl;
#endif
	}
}

int SnesController::stateDecode(struct js_event e)
{
	if (e.value == snesPad::KEY_PRESSED) return 2;
	else if (e.value == snesPad::KEY_RELEASED) return 0;
	else
	{
#ifdef MAP
		cerr << "incoherent button state" << endl;
#endif
		return false;
	}
}

void SnesController::initKeys()
{
	keys.a = 0;
	keys.b = 0;
	keys.x = 0;
	keys.y = 0;
	keys.lb = 0;
	keys.rb = 0;
	keys.start = 0;
	keys.select = 0;
	keys.horiz = 0;
	keys.vert = 0;
	speed = 128;
	lastDrivingAngle = 0;
}

void SnesController::help()
{

	cout << "************************************" << endl;
	cout << "****** Joystick mode commands ******" << endl;
	cout << "************************************" << endl;
	cout << "*        press start to quit       *" << endl;
	cout << "*                                  *" << endl;
	cout << "*           arrows to move         *" << endl;
	cout << "*           L/R to reorient        *" << endl;
	cout << "*           start for menu         *" << endl;
	cout << "*        change speed in menu      *" << endl;
	cout << "*     A boosts value change rate   *" << endl;
	cout << "*                                  *" << endl;
	cout << "*      WARNING : early WIP !!!     *" << endl;
	cout << "************************************" << endl;
}
