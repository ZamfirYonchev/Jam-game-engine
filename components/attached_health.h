/*
 * attached_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_HEALTH_H_
#define COMPONENTS_ATTACHED_HEALTH_H_

#include "health.h"

template<typename EntitySystemT>
class AttachedHealth : public Health
{
public:
	using Base = Health;
	AttachedHealth
		( const EntityID attached_id
		, const double offset_hp
		, const double offset_max_hp
		, const EntitySystemT& entity_system)
	: m_attached_id(attached_id)
	, m_offset_hp(offset_hp)
	, m_offset_max_hp(offset_max_hp)
	, m_entity_system(entity_system)
	{}

    void print(std::ostream& to) const
    {
    	to << "UseAttachedHealth "
    	   << m_attached_id << " "
		   << m_offset_hp << " "
		   << m_offset_max_hp << " ";
    }

    void set_max_hp(double hp) { m_offset_max_hp = hp; }
    void set_hp(double hp) { m_offset_hp = hp; }
    void set_hp_change(double hp_change) {}
    void mod_hp_change(double hp_change) {}
    void update_health(const Time time_diff) {}
    double hp() const
    {
    	return m_entity_system.template entity_component<Health>(m_attached_id).hp() + m_offset_hp;
    }

    double max_hp() const
    {
    	return m_entity_system.template entity_component<Health>(m_attached_id).max_hp() + m_offset_max_hp;
    }
    bool alive() const { return hp() > 0; }
    ProcedureID on_death_exec() const { return ProcedureID(0); }
    void set_on_death_exec(ProcedureID proc_id) {}
    bool stunned() const { return false; }

    EntityID m_attached_id;
private:
    double m_offset_hp, m_offset_max_hp;
    const EntitySystemT& m_entity_system;
};

#endif /* COMPONENTS_ATTACHED_HEALTH_H_ */
