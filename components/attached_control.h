/*
 * attached_control.h
 *
 *  Created on: Jan 28, 2022
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_CONTROL_H_
#define COMPONENTS_ATTACHED_CONTROL_H_

#include "../types.h"

template<typename ControlT>
class AttachedControl
{
public:
	AttachedControl
	( const EntityID attached_id
	, const double offset_horizontal
	, const double offset_vertical
	, const bool offset_attack
	, ComponentAccess<const ControlT> control_accessor
	)
	: m_attached_id(attached_id)
	, m_offset_horizontal(offset_horizontal)
	, m_offset_vertical(offset_vertical)
	, m_offset_attack(offset_attack)
	, m_control_accessor{std::move(control_accessor)}
	{}

    template<typename ExtractorF>
	AttachedControl
	( ExtractorF&& extract
	, ComponentAccess<const ControlT> control_accessor
	)
	: AttachedControl
	  { extract()
	  , extract()
	  , extract()
	  , extract()
	  , std::move(control_accessor)
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseAttachedControl");
    	insert(m_attached_id);
    	insert(m_offset_horizontal);
    	insert(m_offset_vertical);
    }

    double decision_vertical() const
    {
    	return m_control_accessor(m_attached_id).decision_vertical() + m_offset_vertical;
    }

    bool decision_attack() const { return m_control_accessor(m_attached_id).decision_attack() ^ m_offset_attack; }
    double decision_walk() const
    {
    	return m_control_accessor(m_attached_id).decision_walk() + m_offset_horizontal;
    }

    ProcedureID attack_proc_id() const { return ProcedureID{0}; /*TODO m_control_accessor(m_attached_id).attack_proc_id();*/ }

    void set_decision_vertical(double val) { m_offset_vertical = val; }
    void set_decision_attack(bool) {}
    void set_decision_walk(double val) { m_offset_horizontal = val; }
    void mod_decision_vertical(double val) { m_offset_vertical += val; }
    void mod_decision_walk(double val) { m_offset_horizontal += val; }
    void set_attack_proc_id(ProcedureID) {}

    void update_decisions(const Time) {}
    void clear_decisions() {}

private:
    EntityID m_attached_id;
    double m_offset_horizontal, m_offset_vertical;
    bool m_offset_attack;
    //TODO int m_offset_proc_id;
    ComponentAccess<const ControlT> m_control_accessor;
};



#endif /* COMPONENTS_ATTACHED_CONTROL_H_ */
