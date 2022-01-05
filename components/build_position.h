/*
 * build_position.h
 *
 *  Created on: Jul 4, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_BUILD_POSITION_H_
#define COMPONENTS_BUILD_POSITION_H_

#include "../types.h"
#include <iostream>
#include "../math_ext.h"

template<typename PositionT>
class BuildPosition
{
public:
	BuildPosition
	( const EntityID attached_id
	, const double origin_x
	, const double origin_y
	, const ComponentAccess<const PositionT>& position_accessor
	)
	: m_attached_id(attached_id)
	, m_origin_x(origin_x)
	, m_origin_y(origin_y)
	, m_position_accessor(position_accessor)
	{}

    template<typename ExtractorF>
	BuildPosition
	( ExtractorF&& extract
	, const ComponentAccess<const PositionT>& position_accessor
	)
	: BuildPosition
	  { extract().integer()
	  , extract().real()
	  , extract().real()
	  , position_accessor
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
	{
    	insert("UseBuildPosition");
    	insert(m_attached_id);
	}

	void print(std::ostream& to) const
    {
    	to << "UseBuildPosition "
		   << m_attached_id << " ";
    }

    double x() const
    {
    	return min(m_origin_x, m_position_accessor(m_attached_id).x());
    }

    double y() const
    {
    	return min(m_origin_y, m_position_accessor(m_attached_id).y());
    }

    double w() const
    {
    	return abs(m_origin_x - m_position_accessor(m_attached_id).x());
    }

    double h() const
    {
    	return abs(m_origin_y - m_position_accessor(m_attached_id).y());
    }

    void set_x(double) {}
    void set_y(double) {}
    void set_w(double) {}
    void set_h(double) {}

    void mod_x(double) {}
    void mod_y(double) {}
    void mod_w(double) {}
    void mod_h(double) {}

    EntityID m_attached_id;
    double m_origin_x, m_origin_y;

private:
    ComponentAccess<const PositionT> m_position_accessor;
};

#endif /* COMPONENTS_BUILD_POSITION_H_ */
