/*************************************************************************
   DataBuffer  - Utilities class to manage a data stream
							 -------------------
	started                : 07/05/2015
*************************************************************************/

#ifndef DATABUFFER_H
#define DATABUFFER_H


//-------------------------------------------------------- System includes
#include <deque>
#include <cstdint>
#include <pthread.h>

using namespace std;

//------------------------------------------------------------------ Types
enum dataTypes
{
	RAW_ACCEL_X,
	RAW_ACCEL_Y,
	RAW_ACCEL_Z,
	RAW_GYRO_X,
	RAW_GYRO_Y,
	RAW_GYRO_Z,
	RAW_RIGHT_MOTOR_BACK_EMF,
	RAW_LEFT_MOTOR_BACK_EMF,
	RAW_LEFT_MOTOR_PWM,
	RAW_RIGHT_MOTOR_PWM,
	FILTERED_PITCH_IMU,
	FILTERED_ROLL_IMU,
	FILTERED_YAW_IMU,
	FILTERED_ACCEL_X,
	FILTERED_ACCEL_Y,
	FILTERED_ACCEL_Z,
	FILTERED_RIGHT_MOTOR_BACK_EMF,
	FILTERED_LEFT_MOTOR_BACK_EMF,

	QUATERNION_Q0,
	QUATERNION_Q1,
	QUATERNION_Q2,
	QUATERNION_Q3,
	ODOMETER_X,
	ODOMETER_Y,
	ACCELONE_0,
	VELOCITY_X,
	VELOCITY_Y
};


//------------------------------------------------------- Class definition
class DataBuffer
{
	public:

		//---------------------------------------- Constructors/Destructor
		DataBuffer();

		virtual ~DataBuffer();

		//------------------------------------------------- Public methods

		/**
		 * @brief waitForNext : Waits for the next value in the list
		 * @param valueType : The value type
		 * @param returnValue : a reference to the variable in which will be placed the value
		 * @param wait : the wait time (in µs) between each try. If -1, the function isn't blocking
		 * @param timeout : The trying timeout time (in µs)
		 * @return true if the value has been found, false if the timeout came before
		 */
		bool waitForNext(dataTypes valueType, uint16_t& returnValue, int wait = -1, int timeout = 0);


		/**
		 * @brief flush : Flushes the specified queue (can be used when configuring locator, to avoid meaningless)
		 * @param valueType
		 */
		void flush(dataTypes valueType);


		/**
		 * @brief addValue : Adds a new value to the type queue
		 * @param valueType : The type of the value
		 * @param value : The new value
		 */
		void addValue(dataTypes valueType, uint16_t value);

	private:
		pthread_mutex_t lock;
		deque<uint16_t> *_dataValues;


};

#endif // DATABUFFER_H
