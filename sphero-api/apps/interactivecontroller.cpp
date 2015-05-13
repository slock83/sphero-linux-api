#include <iostream>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

#include "interactivecontroller.h"
#include "../API-src/Sphero.hpp"
#include "Keys.hpp"


#define _SPEED 128


InteractiveController::InteractiveController()
{}

void InteractiveController::startInteractiveMode(Sphero *s)
{
	this->s = s;
	if(!isConnected()) return;
	cout << "welcome to interactive mode" <<endl;
	cout << "press q to quit" <<endl;
	cout << "arrow key to move" <<endl;
	cout << "r or t to reorient" <<endl;
	cout << "WARNING : early WIP !!!"<<endl;
	BufferToggle bt;
	bt.off();
	int input;
	int previousHeading = 0;
	unsigned int lastAng =0;
	timeval lastInput, now;
	double elapsedTime;

	// start timer
	gettimeofday(&lastInput, NULL);
	do
	{
		input = getchar();
		if(input == KEY_UP )
		{
			s->roll((uint8_t)_SPEED % 256,(uint16_t) 0 % 0x10000,1);
			lastAng =0;
			gettimeofday(&lastInput, NULL);
		}
		else if(input == KEY_DOWN )
		{
			s->roll((uint8_t)_SPEED % 256,(uint16_t) 180 % 0x10000,1);
			lastAng = 180;
			gettimeofday(&lastInput, NULL);
		}
		else if(input == KEY_RIGHT )
		{
			s->roll((uint8_t)_SPEED % 256,(uint16_t) 90 % 0x10000,1);
			lastAng = 90;
			gettimeofday(&lastInput, NULL);
		}
		else if(input == KEY_LEFT )
		{
			s->roll((uint8_t) _SPEED % 256, (uint16_t) 270 % 0x10000, 1);
			lastAng = 270;
			gettimeofday(&lastInput, NULL);
		}
		else if(input == KEY_R )
		{
			previousHeading+=2;
			if (previousHeading >=360) previousHeading = 0;
			s->setHeading((uint16_t)previousHeading% 360);
			gettimeofday(&lastInput, NULL);
		}
		else if(input == KEY_T )
		{
			previousHeading-=2;
			if (previousHeading <0) previousHeading = 359;
			s->setHeading((uint16_t)previousHeading% 360);
			gettimeofday(&lastInput, NULL);
		}
#ifdef MAP
		cout << "You pressed key ID: " << input << endl;
#endif
		gettimeofday(&now, NULL);
		elapsedTime = (now.tv_sec - lastInput.tv_sec) * 1000.0;      // sec to ms
		elapsedTime += (now.tv_usec - lastInput.tv_usec) / 1000.0;
		//cout << elapsedTime << endl;
		if(elapsedTime >= 120)
			s->roll((uint8_t) 0 % 256, (uint16_t) lastAng % 0x10000, 1);
		usleep(8000);
	}while(input != KEY_Q);

	bt.on();
}

bool InteractiveController::isConnected()
{
	if(s == NULL)
	{
		cerr << "Please connect first" << endl;
		return false;
	}
	return true;
}
