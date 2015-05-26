/*************************************************************************
	Constants  -  Usefull constants for packet configuration
							 -------------------
	début                : ven. 8 mai 2015
*************************************************************************/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//------------------------------------------------------------- Constants
namespace DID
{
	const uint8_t core = 0x00;
	const uint8_t bootloader = 0x01;
	const uint8_t sphero = 0x02;
}

namespace CID
{
	//begin core commands
	const uint8_t ping = 0x01;
	const uint8_t getVersioning = 0x02;
	const uint8_t controlUARTTx = 0x03;

	const uint8_t setDeviceName = 0x10;
	const uint8_t getBluetoothInfo = 0x11;
	const uint8_t setAutoReconnect = 0x12;
	const uint8_t getAutoReconnect = 0x13;

	const uint8_t getPowerState = 0x20;
	const uint8_t setPowerNotification = 0x21;
	const uint8_t sleep = 0x22;
	const uint8_t getVoltageTripPoint = 0x23;
	const uint8_t setVoltageTripPoint = 0x24;
	const uint8_t setInactivityTimeout = 0x25;

	const uint8_t jumpToBootloader = 0x30;

	const uint8_t performLevel1Diagnostic = 0x40;
	const uint8_t performLevel2Diagnostic = 0x41;
	const uint8_t clearCounters = 0x42;

	const uint8_t assignTimeValue = 0x50;
	const uint8_t pollPacketTimes = 0x51;

	//end of core commands


	//begin sphero commands
	const uint8_t setHeading = 0x01;
	const uint8_t setStabilization = 0x02;
	const uint8_t setRotationRate = 0x03;
	const uint8_t setApplicationConfigurationBlock = 0x04;
	const uint8_t getApplicationConfigurationBlock = 0x05;
	const uint8_t getChassisID = 0x07;
	const uint8_t setChassisID = 0x08; //not usable in theory
	const uint8_t selfLevel = 0x09;

	const uint8_t setDataStreaming = 0x11;
	const uint8_t configureCollisionDetection = 0x12;
	const uint8_t configureLocator = 0x13;
	const uint8_t setAccelerometerRange = 0x14;
	const uint8_t readLocator = 0x15;

	const uint8_t setRGBLEDOutput = 0x20;
	const uint8_t setBackLEDOutput = 0x21;
	const uint8_t getRGBLED = 0x22;

	const uint8_t roll = 0x30; //the most usefull
	const uint8_t setBoostWithTime = 0x31; //not supported yet (08/05/15)
	const uint8_t setRawMotorValues = 0x33;
	const uint8_t setMotionTimeout = 0x34;
	const uint8_t setPermanentOptionFlags = 0x35;
	const uint8_t getPermanentOptionFlags = 0x36;
	const uint8_t setTemporaryOptionFlags = 0x37;
	const uint8_t getTemporaryOptionFlags = 0x38;

	const uint8_t getConfigurationBlock = 0x40;
	const uint8_t setDeviceMode = 0x42;
	const uint8_t setConfigurationBlock = 0x43;
	const uint8_t getDeviceMode = 0x44; //someone got drunk and tried to code, result : a completely incoherent order...

	const uint8_t runMacro = 0x50;
	const uint8_t saveTemporaryMacro = 0x51;
	const uint8_t saveMacro = 0x52;
	const uint8_t reinitMacroExecutive = 0x54;
	const uint8_t abortMacro = 0x55;
	const uint8_t getMacroStatus = 0x56;
	const uint8_t setMacroParameter = 0x57;
	const uint8_t appendMacroChunk = 0x58;

	const uint8_t eraseOrbBasicStorage = 0x60;
	const uint8_t appendOrbBasicFragment = 0x61;
	const uint8_t executeOrbBasicProgram = 0x62;
	const uint8_t abortOrbBasicProgram = 0x63;
	const uint8_t submitValueToInputStatement = 0x64;
	//end sphero commands
}

namespace locator_flags
{
	uint8_t const autoCorrection = 0x01;
	uint8_t const noCorrection = 0x00;
}

namespace flags
{
	//for use with setDeviceMode
	const uint8_t normalMode = 0x00;
	const uint8_t hackerMode = 0x01;

	//for use when SEQ (or else) is any
	const uint8_t notNeeded = 0x00;
}

//Flags for data streaming
	//for mask
namespace mask
{
	static uint32_t const RAW_ACCEL_X = 0x80000000;
	static uint32_t const RAW_ACCEL_Y = 0x40000000;
	static uint32_t const RAW_ACCEL_Z = 0x20000000;

	static uint32_t const RAW_GYRO_X = 0x10000000;
	static uint32_t const RAW_GYRO_Y = 0x08000000;
	static uint32_t const RAW_GYRO_Z = 0x04000000;

	static uint32_t const RAW_RIGHT_MOTOR_BACK_EMF = 0x00400000;
	static uint32_t const RAW_LEFT_MOTOR_BACK_EMF = 0x00200000;

	static uint32_t const RAW_LEFT_MOTOR_PWM = 0x00100000;
	static uint32_t const RAW_RIGHT_MOTOR_PWM = 0x00080000;

	static uint32_t const FILTERED_PITCH_IMU = 0x00040000;
	static uint32_t const FILTERED_ROLL_IMU = 0x00020000;
	static uint32_t const FILTERED_YAW_IMU = 0x00010000;

	static uint32_t const FILTERED_ACCEL_X = 0x00008000;
	static uint32_t const FILTERED_ACCEL_Y = 0x00004000;
	static uint32_t const FILTERED_ACCEL_Z = 0x00002000;

	static uint32_t const FILTERED_RIGHT_MOTOR_BACK_EMF = 0x00000040;
	static uint32_t const FILTERED_LEFT_MOTOR_BACK_EMF = 0x00000020;
}

	//for mask2
namespace mask2
{
	static uint32_t const QUATERNION_Q0 = 0x80000000;
	static uint32_t const QUATERNION_Q1 = 0x40000000;
	static uint32_t const QUATERNION_Q2 = 0x20000000;
	static uint32_t const QUATERNION_Q3 = 0x10000000;

	static uint32_t const ODOMETER_X = 0x08000000;
	static uint32_t const ODOMETER_Y = 0x04000000;

	static uint32_t const ACCELONE_0 = 0x02000000;

	static uint32_t const VELOCITY_X = 0x01000000;
	static uint32_t const VELOCITY_Y = 0x00800000;
}

#endif //CONSTANTS_HPP
