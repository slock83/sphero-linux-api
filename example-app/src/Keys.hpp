/*************************************************************************
	keys -- keys for interactive mode
							 -------------------
	start                :08/05/2015
*************************************************************************/

#ifndef _KEYS_HPP
#define _KEYS_HPP


#include <stddef.h>


//------------------------------------------------------------- Constants
namespace keysLegacy
{
	const int _KEY_UP = 0x41;
	const int _KEY_DOWN = 0x42;
	const int _KEY_RIGHT = 0x43;
	const int _KEY_LEFT = 0x44;

	const int _KEY_B = 0x62;
	const int _KEY_C = 0x63;
	const int _KEY_E = 0x65;
	const int _KEY_J = 0x6a;
	const int _KEY_Q = 0x71;
	const int _KEY_R = 0x72;
	const int _KEY_T = 0x74;
	const int _KEY_V = 0x76;
	const int _KEY_Y = 0x79;
}

namespace snesPad
{
	const int16_t KEY_PRESSED = 1;
	const int16_t KEY_RELEASED = 0;
	const uint8_t EVENT_BUTTON = 0x01;
	const uint8_t EVENT_AXIS = 0x02;
	const uint8_t EVENT_INIT = 0x80;
	const uint8_t KEY_X = 0x00;
	const uint8_t KEY_A = 0x01;
	const uint8_t KEY_B = 0x02;
	const uint8_t KEY_Y = 0x03;
	const uint8_t KEY_LB = 0x04;
	const uint8_t KEY_RB = 0x05;
	const uint8_t KEY_SEL = 0x08;
	const uint8_t KEY_START = 0x09;
	const uint8_t AXIS_HORIZ = 0x00;
	const uint8_t AXIS_VERT = 0x01;
}

namespace global
{
	const int _KEY_QUIT = keysLegacy::_KEY_Q;
}

namespace classic
{
	const int _KEY_FORWARD = keysLegacy::_KEY_UP;
	const int _KEY_BACKWARD = keysLegacy::_KEY_DOWN;
	const int _KEY_LEFT = keysLegacy::_KEY_LEFT;
	const int _KEY_RIGHT = keysLegacy::_KEY_RIGHT;

	const int _KEY_BACKLIGHT = keysLegacy::_KEY_B;

	const int _KEY_MODE_CALIBRATE = keysLegacy::_KEY_C;
	const int _KEY_MODE_JOYSTICK = keysLegacy::_KEY_J;
}

namespace calibrate
{
	const int _KEY_LEFT_2 = keysLegacy::_KEY_R;
	const int _KEY_LEFT_10 = keysLegacy::_KEY_E;
	const int _KEY_RIGHT_2 = keysLegacy::_KEY_T;
	const int _KEY_RIGHT_10 = keysLegacy::_KEY_Y;

	const int _KEY_VALIDATE = keysLegacy::_KEY_V;
	const int _KEY_RETURN = keysLegacy::_KEY_B;
}

enum mode
{
	CLASSIC,
	CALIBRATE,
	JOYSTICK
};

#endif //_KEYS_HPP
