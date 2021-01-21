/*
 * build_position.h
 *
 *  Created on: Jul 4, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_BUILD_POSITION_H_
#define COMPONENTS_BUILD_POSITION_H_

#include "position.h"
#include "../types.h"
#include <iostream>
#include "../math_ext.h"

template<typename EntitySystemT>
class BuildPosition : public Position
{
public:
	using Base = Position;
	BuildPosition
		(const EntityID attached_id
	   , const double origin_x
	   , const double origin_y
	   , const EntitySystemT& entity_system)
	: m_attached_id(attached_id)
    , m_origin_x(origin_x)
    , m_origin_y(origin_y)
	, m_entity_system(entity_system)
    {}

    void print(std::ostream& to) const
    {
    	to << "UseBuildPosition "
		   << m_attached_id << " ";
    }

    double x() const
    {
    	return min(m_origin_x, m_entity_system.entity_component(m_attached_id, Position::null).x());
    }

    double y() const
    {
    	return min(m_origin_y, m_entity_system.entity_component(m_attached_id, Position::null).y());
    }

    double w() const
    {
    	return abs(m_origin_x - m_entity_system.entity_component(m_attached_id, Position::null).x());
    }

    double h() const
    {
    	return abs(m_origin_y - m_entity_system.entity_component(m_attached_id, Position::null).y());
    }

    void set_x(double val) {}
    void set_y(double val) {}
    void set_w(double val) {}
    void set_h(double val) {}

    void mod_x(double val) {}
    void mod_y(double val) {}
    void mod_w(double val) {}
    void mod_h(double val) {}

    EntityID m_attached_id;
    double m_origin_x, m_origin_y;

private:
    const EntitySystemT& m_entity_system;
};

#endif /* COMPONENTS_BUILD_POSITION_H_ */
