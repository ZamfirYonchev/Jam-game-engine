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

class BuildPosition : public Position
{
public:
	using Base = Position;
	BuildPosition(EntityID self_id, EntityID attached_id, double origin_x, double origin_y)
    : m_self_id(self_id)
	, m_attached_id(attached_id)
    , m_origin_x(origin_x)
    , m_origin_y(origin_y)
    {}

    void print(std::ostream& to) const
    {
    	to << "UseBuildPosition "
		   << m_self_id << " "
		   << m_attached_id << " "
    	   << m_origin_x << " "
		   << m_origin_y << " ";
    }

    double x() const;
    double y() const;
    double w() const;
    double h() const;

    void set_x(double val) {}
    void set_y(double val) {}
    void set_w(double val) {}
    void set_h(double val) {}

    void mod_x(double val) {}
    void mod_y(double val) {}
    void mod_w(double val); //implement solidify
    void mod_h(double val) {}

private:
    EntityID m_self_id, m_attached_id;
    double m_origin_x, m_origin_y;
};

#endif /* COMPONENTS_BUILD_POSITION_H_ */
