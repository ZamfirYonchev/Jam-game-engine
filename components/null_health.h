/*
 * null_health.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_HEALTH_H_
#define COMPONENTS_NULL_HEALTH_H_

class NullHealth
{
public:
	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullHealth");
    }

    void set_max_hp(double) {}
    void set_hp(double) {}
    void set_hp_change(double) {}
    void mod_hp_change(double) {}
    void update_health(const Time) {}
    double hp() const { return 0; }
    double max_hp() const { return 0; }
    bool alive() const { return true; }
    ProcedureID on_death_exec() const { return ProcedureID(0); }
    void set_on_death_exec(ProcedureID) {}
    bool stunned() const { return false; }
};

#endif /* COMPONENTS_NULL_HEALTH_H_ */
