/*
 * collision_system.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef SYSTEMS_COLLISION_SYSTEM_H_
#define SYSTEMS_COLLISION_SYSTEM_H_

#include "system_base.h"
#include <unordered_map>
#include <unordered_set>
#include "../components/collision.h"

class CollisionSystem : public SystemBase
{
public:
    void update(const Time time_diff);

    void clear()
    {
    	SystemBase::clear();
    	entities_per_region.clear();
    	regions_per_entity.clear();
    }

private:
    struct RegionPosition
	{
    	int x; int y;

    	constexpr bool operator==(const RegionPosition &p) const
    	{
    		return x == p.x && y == p.y;
    	}

    	constexpr bool operator!=(const RegionPosition &p) const
		{
    		return !(*this == p);
		}

	};

    struct RegionPositionHashFn
    {
    	std::size_t operator() (const RegionPosition &p) const
    	{
    		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    	}
    };

    std::unordered_map<RegionPosition, std::unordered_set<EntityID>, RegionPositionHashFn> entities_per_region;
    std::unordered_map<EntityID, Collision::RegionLocation> regions_per_entity;
	static const unsigned int REGION_W = 32;
    static const unsigned int REGION_H = 32;
};

#endif /* SYSTEMS_COLLISION_SYSTEM_H_ */
