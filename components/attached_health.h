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

class Health;

class AttachedHealth
{
public:
	AttachedHealth
	( const EntityID attached_id
	, const double offset_hp
	, const double offset_max_hp
	, const ComponentAccess<const Health>& health_accessor
	)
	: m_attached_id(attached_id)
	, m_offset_hp(offset_hp)
	, m_offset_max_hp(offset_max_hp)
	, m_health_accessor{health_accessor}
	{}

    template<typename ExtractorF>
	AttachedHealth
	( ExtractorF&& extract
	, const ComponentAccess<const Health>& health_accessor
	)
	: AttachedHealth
	  { extract().integer()
	  , extract().real()
	  , extract().real()
	  , health_accessor
	  }
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
    void set_hp_change(double) {}
    void mod_hp_change(double) {}
    void update_health(const Time) {}
    double hp() const;
    double max_hp() const;
    bool alive() const { return hp() > 0; }
    ProcedureID on_death_exec() const { return ProcedureID(0); }
    void set_on_death_exec(ProcedureID) {}
    bool stunned() const { return false; }

    EntityID m_attached_id;
private:
    double m_offset_hp, m_offset_max_hp;
    ComponentAccess<const Health> m_health_accessor;
};

#endif /* COMPONENTS_ATTACHED_HEALTH_H_ */
