/*************************************************************************
	keys -- keys for interactive mode
							 -------------------
	start                :08/05/2015
*************************************************************************/

#ifndef KEYS_HPP
#define KEYS_HPP

//------------------------------------------------------------- Constants
namespace keys
{
	const int KEY_UP = 0x41;
	const int KEY_DOWN = 0x42;
	const int KEY_RIGHT = 0x43;
	const int KEY_LEFT = 0x44;

	const int KEY_B = 0x62;
	const int KEY_C = 0x63;
	const int KEY_E = 0x65;
	const int KEY_Q = 0x71;
	const int KEY_R = 0x72;
	const int KEY_T = 0x74;
	const int KEY_Y = 0x79;
}

namespace global
{
	const int KEY_QUIT = keys::KEY_Q;
}

namespace classic
{
	const int KEY_FORWARD = keys::KEY_UP;
	const int KEY_BACKWARD = keys::KEY_DOWN;
	const int KEY_LEFT = keys::KEY_LEFT;
	const int KEY_RIGHT = keys::KEY_RIGHT;

	const int KEY_BACKLIGHT = keys::KEY_B;

	const int KEY_MODE_CALIBRATE = keys::KEY_C;
}

namespace calibrate
{
	const int KEY_LEFT_2 = keys::KEY_R;
	const int KEY_LEFT_10 = keys::KEY_E;
	const int KEY_RIGHT_2 = keys::KEY_T;
	const int KEY_RIGHT_10 = keys::KEY_Y;

	const int KEY_VALIDATE = keys::KEY_B;
	const int KEY_RETURN = keys::KEY_B;
}

enum mode
{
	CLASSIC,
	CALIBRATE
};

#endif //KEYS_HPP
