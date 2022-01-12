/*
 * attached_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_POSITION_H_
#define COMPONENTS_ATTACHED_POSITION_H_

#include "../types.h"
#include "../utilities.h"

template<typename PositionT>
class AttachedPosition
{
public:
    AttachedPosition
	( const EntityID attached_id
    , const double offset_x
    , const double offset_y
    , const double offset_w
    , const double offset_h
    , ComponentAccess<const PositionT> position_accessor
    )
    : m_attached_id(attached_id)
    , m_offset_x(offset_x)
    , m_offset_y(offset_y)
    , m_offset_w(offset_w)
    , m_offset_h(offset_h)
    , m_position_accessor{std::move(position_accessor)}
    {}

    template<typename ExtractorF>
	AttachedPosition
	( ExtractorF&& extract
	, ComponentAccess<const PositionT> position_accessor
	)
	: m_attached_id{extract()}
	, m_offset_x{extract()}
	, m_offset_y{extract()}
	, m_offset_w{extract()}
	, m_offset_h{extract()}
	, m_position_accessor{std::move(position_accessor)}
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
	{
    	insert("UseAttachedPosition");
    	insert(m_offset_x);
    	insert(m_offset_y);
    	insert(m_offset_w);
    	insert(m_offset_h);
	}

    double x() const
    {
    	return m_position_accessor(m_attached_id).x()
    		+ absolute_or_scaled(m_offset_x, m_position_accessor(m_attached_id).w());
    }

    double y() const
    {
    	return m_position_accessor(m_attached_id).y()
    		+ absolute_or_scaled(m_offset_y, m_position_accessor(m_attached_id).h());
    }

    double w() const
    {
    	return m_position_accessor(m_attached_id).w()
    		 + absolute_or_scaled(m_offset_w, m_position_accessor(m_attached_id).w());
    }

    double h() const
    {
    	return m_position_accessor(m_attached_id).h()
    		 + absolute_or_scaled(m_offset_h, m_position_accessor(m_attached_id).h());
    }

    void set_x(double) {}
    void set_y(double) {}
    void set_w(double) {}
    void set_h(double) {}

    void mod_x(double val) { m_offset_x += val; }
    void mod_y(double val) { m_offset_y += val; }
    void mod_w(double val) { m_offset_w += val; }
    void mod_h(double val) { m_offset_h += val; }

    EntityID m_attached_id;

private:
    double m_offset_x, m_offset_y, m_offset_w, m_offset_h;
    ComponentAccess<const PositionT> m_position_accessor;
};


#endif /* COMPONENTS_ATTACHED_POSITION_H_ */
