/*
 * attached_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_HEALTH_H_
#define COMPONENTS_ATTACHED_HEALTH_H_

#include "../types.h"
#include <ostream>

template<typename HealthT>
class AttachedHealth
{
public:
	AttachedHealth
	( const EntityID attached_id
	, const double offset_hp
	, const double offset_max_hp
	, const ComponentAccess<const HealthT>& health_accessor
	)
	: m_attached_id(attached_id)
	, m_offset_hp(offset_hp)
	, m_offset_max_hp(offset_max_hp)
	, m_health_accessor{health_accessor}
	{}

    template<typename ExtractorF>
	AttachedHealth
	( ExtractorF&& extract
	, const ComponentAccess<const HealthT>& health_accessor
	)
	: AttachedHealth
	  { extract().integer()
	  , extract().real()
	  , extract().real()
	  , health_accessor
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseAttachedHealth");
    	insert(m_attached_id);
    	insert(m_offset_hp);
    	insert(m_offset_max_hp);
    }

    void print(std::ostream& to) const
    {
    	to << "UseAttachedHealth "
    	   << m_attached_id << " "
		   << m_offset_hp << " "
		   << m_offset_max_hp << " ";
    }

    void set_max_hp(double hp) { m_offset_max_hp = hp; }
    void set_hp(double hp) { m_offset_hp = hp; }
    void set_hp_change(double) {}
    void mod_hp_change(double) {}
    void update_health(const Time) {}
    double hp() const
    {
    	return m_health_accessor(m_attached_id).hp() + m_offset_hp;
    }

    double max_hp() const
    {
    	return m_health_accessor(m_attached_id).max_hp() + m_offset_max_hp;
    }

    bool alive() const { return hp() > 0; }
    ProcedureID on_death_exec() const { return ProcedureID(0); }
    void set_on_death_exec(ProcedureID) {}
    bool stunned() const { return false; }

    EntityID m_attached_id;
private:
    double m_offset_hp, m_offset_max_hp;
    ComponentAccess<const HealthT> m_health_accessor;
};

#endif /* COMPONENTS_ATTACHED_HEALTH_H_ */
