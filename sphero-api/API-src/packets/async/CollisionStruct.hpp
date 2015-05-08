/*************************************************************************
   CollisionStruct  - 
                             -------------------
	started                : 07/05/2015
*************************************************************************/

#ifndef COLLISIONSTRUCT_HPP
#define COLLISIONSTRUCT_HPP

#include <cstdint>

//------------------------------------------------------- Class definition

/**
 * @brief CollisionStruct : Structure with sphero informations when
 * 							collision detected
 *
 **/
struct CollisionStruct
{
	//---------------------------------------------------------- Types
	enum axis_t
	{
		XAXIS, YAXIS
	};

	//---------------------------------------------- Public attributes

	/**
	 * @brief CollisionStruct : convert axis raw data to enun axis_t
	 *
	 * @param rawAxis : raw information from sphero
	 *
	 * @return TODO 
	 *
	 **/
	
	axis_t setAxis(uint8_t rawAxis);
	
	uint16_t impact_component_x;
	uint16_t impact_component_y;
	uint16_t impact_component_z;
	
	axis_t threshold_axis;
	
	uint16_t magnitude_component_x;
	uint16_t magnitude_component_y;
	
	uint8_t speed;
	
	uint32_t timestamp;
};

#endif // COLLISIONSTRUCT_HPP

