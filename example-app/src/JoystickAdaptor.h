#ifndef JOYSTICKADAPTOR_H
#define JOYSTICKADAPTOR_H

#include <pthread.h>
#include <deque>
#include <string>

using namespace std;

enum eventType{
	AXIS_1,
	BUTTONS,
	NONE
};

enum eventBtn{
	AXIS_X,
	AXIS_Y,

	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,

	LEFT_PRESS,
	RIGHT_PRESS,

	START,
	SELECT
};


struct JoystickEvent
{
	eventType type;
	eventBtn buttonType;

	int value;
};


class JoystickAdaptor
{
	public:
		JoystickAdaptor();


		/**
		 * @brief startListener : Starts the joystick listener
		 * @param joystickIndex : The index of the joystick
		 * @return true if the listener was successfully started
		 */
		bool startListener(int joystickIndex = 0);

		/**
		 * @brief stop : Stops the listener
		 */
		void stop();

		/**
		 * @brief next : Returns the next event into the events list
		 * @return the event if there is one, NULL otherwise
		 */
		JoystickEvent next();

	private:
		pthread_t _listener;
		pthread_mutex_t _readerMutex;

		deque<JoystickEvent> _events;
		bool _read;

		/**
		 * @brief listenJoystick : Thread entry function for joystick listening
		 * @param ifListener : A pointer to the ifstream joystick listener
		 * @return NULL
		 */
		static void* listenJoystick(void* init);

		/**
		 * @brief addEvent : Adds an event to the queue
		 * @param ev : The new event
		 */
		void addEvent(JoystickEvent ev);

		/**
		 * @brief interpret : Interprets the data into an event
		 * @param data : The data to interpret
		 * @return the event interpreted
		 */
		static JoystickEvent interpret(int* data);
};

#endif // JOYSTICKADAPTOR_H
