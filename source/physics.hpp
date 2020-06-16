#include <3ds.h>
#include <m3dia.hpp>

#include "gameObject.hpp"

namespace Physics
{
    /**
     *  
     *  @brief
     *  @param a
     *  @param b
     *  @returns
     */
    bool checkCollision(GameObject a, GameObject b)
    {     
        m3d::BoundingBox first = a.getAABB();           
        m3d::BoundingBox second = b.getAABB();
        
        if(first == NULL || second == NULL){
            return false;
        }else
        {
            return first.intersects(second);
        }
    }
}