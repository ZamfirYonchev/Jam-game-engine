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
#include "../command_value.h"

class Position;

class BuildPosition
{
public:
	BuildPosition
	( const EntityID attached_id
	, const double origin_x
	, const double origin_y
	, const std::function<const Position&(const EntityID id)>& position_accessor
	)
	: m_attached_id(attached_id)
	, m_origin_x(origin_x)
	, m_origin_y(origin_y)
	, m_position_accessor(position_accessor)
	{}

    template<typename ExtractorF>
	BuildPosition
	( ExtractorF&& extract
	, const std::function<const Position&(const EntityID id)>& position_accessor
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
    	insert(CommandValue{"UseBuildPosition"});
    	insert(CommandValue{m_attached_id, 0});
	}

	void print(std::ostream& to) const
    {
    	to << "UseBuildPosition "
		   << m_attached_id << " ";
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
    void mod_w(double val) {}
    void mod_h(double val) {}

    EntityID m_attached_id;
    double m_origin_x, m_origin_y;

private:
   std::function<const Position&(const EntityID id)> m_position_accessor;
};

#endif /* COMPONENTS_BUILD_POSITION_H_ */
