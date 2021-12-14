/*
 * attached_directional_position.h
 *
 *  Created on: Jan 30, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_
#define COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_

#include "../types.h"
#include <ostream>

class Position;
class Control;

class AttachedDirectionalPosition
{
public:
	AttachedDirectionalPosition
	( const EntityID attached_id
    , const double offset_x
    , const double offset_y
    , const double w
    , const double h
    , const ComponentAccess<const Position>& position_accessor
    , const ComponentAccess<const Control>& control_accessor
    )
	: m_attached_id{attached_id}
	, m_offset_x{offset_x}
	, m_offset_y{offset_y}
	, m_w{w}
	, m_h{h}
	, m_position_accessor{position_accessor}
	, m_control_accessor{control_accessor}
	{}

    template<typename ExtractorF>
	AttachedDirectionalPosition
	( ExtractorF&& extract
	, const ComponentAccess<const Position>& position_accessor
	, const ComponentAccess<const Control>& control_accessor
	)
	: AttachedDirectionalPosition
	  { extract().integer()
	  , extract().real()
	  , extract().real()
	  , extract().real()
	  , extract().real()
	  , position_accessor
	  , control_accessor
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
	{
    	insert("UseAttachedDirectionalPosition");
    	insert(m_offset_x);
    	insert(m_offset_y);
    	insert(m_w);
    	insert(m_h);
	}

    void print(std::ostream& to) const
    {
    	to << "UseAttachedDirectionalPosition "
    	   << m_offset_x << " "
		   << m_offset_y << " "
		   << m_w << " "
		   << m_h << " ";
    }

    double x() const;

    double y() const;

    double w() const { return m_w; }

    double h() const { return m_h; }

    void set_x(double) {}
    void set_y(double) {}
    void set_w(double) {}
    void set_h(double) {}

    void mod_x(double) {}
    void mod_y(double) {}
    void mod_w(double) {}
    void mod_h(double) {}

    EntityID m_attached_id;

private:
    double m_offset_x, m_offset_y, m_w, m_h;
    ComponentAccess<const Position> m_position_accessor;
    ComponentAccess<const Control> m_control_accessor;
};


#endif /* COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_ */
