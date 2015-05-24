
#include <fstream>
#include <sstream>
#include <deque>

using namespace std;

#include "JoystickAdaptor.h"


struct threadInit{
		ifstream* ifstream;
		JoystickAdaptor* adaptor;
};


JoystickAdaptor::JoystickAdaptor(): _read(true)
{
	pthread_mutex_init(&_readerMutex, NULL);
}


/**
 * @brief startListener : Starts the joystick listener
 * @param joystickIndex : The index of the joystick
 * @return true if the listener was successfully started
 */
bool JoystickAdaptor::startListener(int joystickIndex)
{
	_events.clear();
	string fileLoc;
	system("ls /dev/input/by-path/ | grep joystick | grep -v event > ./tmp");

	ifstream inputList ("tmp", ios::in);
	if (inputList.is_open())
	{
		for(int i = 0; i < joystickIndex; ++i)
			inputList >> fileLoc;
		inputList >> fileLoc;
		inputList.close();
	}

	stringstream ss("");
	ss << "/dev/input/by-path/" << fileLoc;
	fileLoc = ss.str();

	ifstream* joystickInput = new ifstream(fileLoc.c_str(), ios::in);

	if(joystickInput->is_open())
	{
		threadInit ti;
		ti.adaptor = this;
		ti.ifstream = joystickInput;
		if(pthread_create(&_listener, NULL, listenJoystick, &ti))
			return true;
	}
	return false;
}


/**
 * @brief stop : Stops the listener
 */
void JoystickAdaptor::stop()
{
	_read = false;
}


/**
 * @brief next : Returns the next event into the events list
 * @return the event if there is one, NULL otherwise
 */
JoystickEvent JoystickAdaptor::next()
{
	pthread_mutex_lock(&_readerMutex);

	if(_events.size() < 1)
	{
		pthread_mutex_unlock(&_readerMutex);
		JoystickEvent ev;
		ev.type = NONE;
		return ev;
	}

	JoystickEvent ev = _events[0];
	_events.pop_front();

	pthread_mutex_unlock(&_readerMutex);

	return ev;
}


/**
 * @brief listenJoystick : Thread entry function for joystick listening
 * @param ifListener : A pointer to the ifstream joystick listener
 * @return NULL
 */
void* JoystickAdaptor::listenJoystick(void* init)
{
	threadInit* initializer = (threadInit*) init;
	ifstream* joystickInput = initializer->ifstream;
	JoystickAdaptor* adaptor = initializer->adaptor;

	while(adaptor->_read)
	{
		for(int i = 0; i < 4; ++i)
			joystickInput->get();

		int data[4];
		for(int i = 0; i < 4; ++i)
			data[i] = joystickInput->get();

		JoystickEvent ev = interpret(data);

		if(ev.type != NONE)
			adaptor->addEvent(ev);
	}
	joystickInput->close();
	delete joystickInput;
	return NULL;
}


/**
 * @brief addEvent : Adds an event to the queue
 * @param ev : The new event
 */
void JoystickAdaptor::addEvent(JoystickEvent ev)
{
	pthread_mutex_lock(&_readerMutex);

	_events.push_back(ev);

	pthread_mutex_unlock(&_readerMutex);
}


/**
 * @brief interpret : Interprets the data into an event
 * @param data : The data to interpret
 * @return the event interpreted
 */
JoystickEvent JoystickAdaptor::interpret(int *data)
{
	JoystickEvent ev;
	ev.type = NONE;

	switch(data[2])
	{
		case 1:
			ev.type = BUTTONS;
			ev.value = data[0];

			if(data[3] < 4)
				ev.buttonType = BUTTON_0 + data[3];
			else if(data[3] == 8)
				ev.buttonType = SELECT;
			else if(data[3] == 9)
				ev.buttonType = START;
			else if(data[3] == 4)
				ev.buttonType = LEFT_PRESS;
			else if(data[3] == 5)
					ev.buttonType = RIGHT_PRESS;

			break;
		case 2:
			ev.type = AXIS_1;

			if(data[0] == 0)
				ev.value = 0;
			else if (data[0] == 1)
				ev.value = -127;
			else
				ev.value = 128;

			switch(data[3])
			{
				case 1:
					ev.buttonType = AXIS_Y;
					break;
				case 0:
					ev.buttonType = AXIS_X;
					break;
			}
			break;
	}
	return ev;
}
