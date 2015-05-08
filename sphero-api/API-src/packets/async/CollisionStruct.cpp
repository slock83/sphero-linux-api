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
	return threshold_axis = (rawAxis == 0) ? axis_t::XAXIS : axis_t::YAXIS;
}
