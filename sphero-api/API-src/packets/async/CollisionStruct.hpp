/*************************************************************************
   SpheroCollisionPacket  - Represents an asynchronous collision packet
                             -------------------
	started                : 07/05/2015
*************************************************************************/

#ifndef COLLISIONSTRUCT_HPP
#define COLLISIONSTRUCT_HPP

//--------------------------------------------------------- Local includes

//------------------------------------------------------- Class definition

/**
 * @brief CollisionStruct : TODO
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

