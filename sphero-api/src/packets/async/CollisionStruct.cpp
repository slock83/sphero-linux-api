/*************************************************************************
   CollisionStruct  - 
                             -------------------
    début                : jeu. 08 mai 2015
*************************************************************************/

//-------------------------------------------------------- System includes

//--------------------------------------------------------- Local includes
#include "CollisionStruct.hpp"


//-------------------------------------------------------------- Constants


//--------------------------------------------------------- Public methods

CollisionStruct::axis_t CollisionStruct::setAxis(uint8_t rawAxis)
{
	if(rawAxis == 0)
		return threshold_axis = axis_t::XAXIS;
	else if(rawAxis == 1)
		return threshold_axis = axis_t::YAXIS;
	
	return threshold_axis = axis_t::BADAXIS;
}
