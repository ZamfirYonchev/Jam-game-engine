/*
 * attached_directional_position.h
 *
 *  Created on: Jan 30, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_
#define COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_

#include "../types.h"
#include "../components/control_enums.h"

template<typename PositionT, typename ControlT>
class AttachedDirectionalPosition
{
public:
	AttachedDirectionalPosition
	( const EntityID attached_id
    , const double offset_x
    , const double offset_y
    , const double w
    , const double h
    , ComponentAccess<const PositionT> position_accessor
    , ComponentAccess<const ControlT> control_accessor
    )
	: m_attached_id{attached_id}
	, m_offset_x{offset_x}
	, m_offset_y{offset_y}
	, m_w{w}
	, m_h{h}
	, m_position_accessor{std::move(position_accessor)}
	, m_control_accessor{std::move(control_accessor)}
	{}

    template<typename ExtractorF>
	AttachedDirectionalPosition
	( ExtractorF&& extract
	, ComponentAccess<const PositionT> position_accessor
	, ComponentAccess<const ControlT> control_accessor
	)
	: AttachedDirectionalPosition
	  { extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , std::move(position_accessor)
	  , std::move(control_accessor)
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

    double x() const
    {
    	const auto& attached_position = m_position_accessor(m_attached_id);
    	return attached_position.x()
    		 + attached_position.w()/2
    		 + m_offset_x * (1 - 2*(m_control_accessor(m_attached_id).look_dir() == LookDir::LEFT))
    		 - m_w/2;
    }

    double y() const
    {
    	const auto& attached_position = m_position_accessor(m_attached_id);
    	return attached_position.y()
    		 + attached_position.h()/2
    		 + m_offset_y
    		 - m_h/2;
    }

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
    ComponentAccess<const PositionT> m_position_accessor;
    ComponentAccess<const ControlT> m_control_accessor;
};


#endif /* COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_ */
