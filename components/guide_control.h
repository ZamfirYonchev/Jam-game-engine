/*
 * guide_control.h
 *
 *  Created on: Dec 7, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_GUIDE_CONTROL_H_
#define COMPONENTS_GUIDE_CONTROL_H_

#include "../math_ext.h"
#include "../types.h"

template<typename PositionT>
class GuideControl
{
public:
	GuideControl
		(const EntityID target_id
	   , const double range
	   , const EntityID self_id
	   , ComponentAccess<const PositionT> position_accessor
	   )
	: m_target_id(target_id)
	, m_walk_dir(0)
	, m_vertical(0)
	, m_range(range)
	, m_self_id(self_id)
	, m_position_accessor(std::move(position_accessor))
	{}

    template<typename ExtractorF, typename SelfIDObtainerF>
	GuideControl
	( ExtractorF&& extract
	, const SelfIDObtainerF& obtain_self_id
	, ComponentAccess<const PositionT> position_accessor
	)
	: GuideControl
	  { extract()
	  , extract()
	  , obtain_self_id()
	  , std::move(position_accessor)
	  }
	{}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseGuideControl");
    	insert(m_target_id);
    	insert(m_range);
    }

    double decision_vertical() const { return m_vertical; }
    bool decision_attack() const { return false; }
    double decision_walk() const { return m_walk_dir; }
    ProcedureID attack_proc_id() const { return ProcedureID(0); }

    void set_decision_vertical(double) {}
    void set_decision_attack(bool) {}
    void set_decision_walk(double) {}
    void mod_decision_vertical(double) {}
    void mod_decision_walk(double) {}
    void set_attack_proc_id(ProcedureID) {}

    void update_decisions(const Time time_diff)
    {
    	const auto& self_position = m_position_accessor(m_self_id);
    	const auto& target_position = m_position_accessor(m_target_id);

    	if(target_position)
    	{
    		const double distance_x = target_position.x() - self_position.x() + (target_position.w() - self_position.w())/2.0;
    		const double distance_y = target_position.y() - self_position.y() + (target_position.h() - self_position.h())/2.0;

    		m_walk_dir = sign(distance_x) * (abs(distance_x) > m_range);
    		m_vertical = distance_y > 100 && distance_y < 200 && abs(distance_x) < 200;
    	}
    	else
    	{
    		//error m_target_id
    	}
    }

    void clear_decisions()
    {
        m_walk_dir = 0.0;
        m_vertical = 0.0;
    }

private:
    EntityID m_target_id;
    double m_walk_dir, m_vertical;
    double m_range;
    EntityID m_self_id;
    ComponentAccess<const PositionT> m_position_accessor;
};



#endif /* COMPONENTS_GUIDE_CONTROL_H_ */
