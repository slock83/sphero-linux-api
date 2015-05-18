/*************************************************************************
	keys -- keys for interactive mode
							 -------------------
	start                :08/05/2015
*************************************************************************/

#ifndef _KEYS_HPP
#define _KEYS_HPP

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
	const int _KEY_Q = 0x71;
	const int _KEY_R = 0x72;
	const int _KEY_T = 0x74;
	const int _KEY_V = 0x76;
	const int _KEY_Y = 0x79;
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
	CALIBRATE
};

#endif //_KEYS_HPP
