/*
 * guide_control.h
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_GUIDE_CONTROL_H_
#define COMPONENTS_GUIDE_CONTROL_H_

#include "control_enums.h"
#include "../math_ext.h"
#include "../types.h"
#include <ostream>

class Position;

class GuideControl
{
public:
	GuideControl
		(const EntityID self_id
	   , const EntityID target_id
	   , const double range
	   , const ComponentAccess<const Position>& position_accessor
	   )
	: m_self_id(self_id)
	, m_target_id(target_id)
	, m_walk_dir(0)
	, m_vertical(0)
	, m_look_dir(LookDir::RIGHT)
	, m_range(range)
	, m_position_accessor(position_accessor)
	{}

    template<typename ExtractorF, typename SelfIDObtainerF>
	GuideControl
	( ExtractorF&& extract
	, SelfIDObtainerF&& obtain_self_id
	, const ComponentAccess<const Position>& position_accessor
	)
	: GuideControl
	  { obtain_self_id()
	  , extract().integer()
	  , extract().real()
	  , position_accessor
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseGuideControl "
    	   << m_target_id << " "
    	   << m_range << " ";
    }

    double decision_vertical() const { return m_vertical; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return ProcedureID(0); }
    LookDir look_dir() const { return m_look_dir; }

    void set_decision_vertical(double) {}
    void set_decision_attack(bool) {}
    void set_decision_walk(double) {}
    void mod_decision_vertical(double) {}
    void mod_decision_walk(double) {}
    void set_attack_proc_id(ProcedureID) {}
    void set_look_dir(LookDir val) { m_look_dir = val; }

    void update_decisions(const Time time_diff);
    void clear_decisions()
    {
        m_walk_dir = 0.0;
        m_vertical = 0.0;
    }

    EntityID m_self_id, m_target_id;

private:
    double m_walk_dir, m_vertical;
    LookDir m_look_dir;
    double m_range;
    ComponentAccess<const Position> m_position_accessor;
};



#endif /* COMPONENTS_GUIDE_CONTROL_H_ */
