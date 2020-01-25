/*
 * attached_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_HEALTH_H_
#define COMPONENTS_ATTACHED_HEALTH_H_

#include "health.h"

class AttachedHealth : public Health
{
public:
	AttachedHealth(EntityID attached_id, double offset_hp, double offset_max_hp)
	: m_attached_id(attached_id)
	, m_offset_hp(offset_hp)
	, m_offset_max_hp(offset_max_hp)
	{}

    void set_max_hp(double hp) { m_offset_max_hp = hp; }
    void set_hp(double hp) { m_offset_hp = hp; }
    void set_hp_change(double hp_change) {}
    void mod_hp_change(double hp_change) {}
    void update_health(double time_diff) {}
    double hp() const;
    double max_hp() const;
    bool alive() const { return hp() > 0; }
    ProcedureID on_death_exec() const { return -1; }
    void set_on_death_exec(ProcedureID proc_id) {}
    bool stunned() const { return false; }

private:
    EntityID m_attached_id;
    double m_offset_hp, m_offset_max_hp;
};

#endif /* COMPONENTS_ATTACHED_HEALTH_H_ */
