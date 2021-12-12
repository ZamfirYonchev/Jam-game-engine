/*
 * attached_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_POSITION_H_
#define COMPONENTS_ATTACHED_POSITION_H_

#include "../types.h"
#include <ostream>
#include <functional>
#include <iostream>
#include "../command_value.h"

class Position;

class AttachedPosition
{
public:
    AttachedPosition
	( const EntityID attached_id
    , const double offset_x
    , const double offset_y
    , const double offset_w
    , const double offset_h
    , const std::function<const Position&(const EntityID id)>& position_accessor
    )
    : m_attached_id(attached_id)
    , m_offset_x(offset_x)
    , m_offset_y(offset_y)
    , m_offset_w(offset_w)
    , m_offset_h(offset_h)
    , m_position_accessor{position_accessor}
    {}

    template<typename ExtractorF>
	AttachedPosition
	( ExtractorF&& extract
	, const std::function<const Position&(const EntityID id)>& position_accessor
	)
	: m_attached_id{extract().integer()}
	, m_offset_x{extract().real()}
	, m_offset_y{extract().real()}
	, m_offset_w{extract().real()}
	, m_offset_h{extract().real()}
	, m_position_accessor{position_accessor}
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
	{
    	insert(CommandValue{"UseAttachedPosition"});
    	insert(CommandValue{m_offset_x});
    	insert(CommandValue{m_offset_y});
    	insert(CommandValue{m_offset_w});
    	insert(CommandValue{m_offset_h});
	}

    void print(std::ostream& to) const
    {
    	to << "UseAttachedPosition "
    	   << m_offset_x << " "
		   << m_offset_y << " "
		   << m_offset_w << " "
		   << m_offset_h << " ";
    }

    double x() const;
    double y() const;
    double w() const;
    double h() const;

    void set_x(double val) {}
    void set_y(double val) {}
    void set_w(double val) {}
    void set_h(double val) {}

    void mod_x(double val) { m_offset_x += val; }
    void mod_y(double val) { m_offset_y += val; }
    void mod_w(double val) { m_offset_w += val; }
    void mod_h(double val) { m_offset_h += val; }

    EntityID m_attached_id;

private:
    double m_offset_x, m_offset_y, m_offset_w, m_offset_h;
    std::function<const Position&(const EntityID id)> m_position_accessor;
};


#endif /* COMPONENTS_ATTACHED_POSITION_H_ */
