/*
 * attached_directional_position.h
 *
 *  Created on: Jan 30, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_
#define COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_

#include "position.h"
#include "control.h"
#include "../types.h"
#include "../commands/use_component_command.h"

template<typename EntitySystemT>
class AttachedDirectionalPosition : public Position
{
public:
	using Base = Position;
    AttachedDirectionalPosition
		(const EntityID attached_id
	   , const double offset_x
	   , const double offset_y
	   , const double w
	   , const double h
	   , const EntitySystemT& entity_system)
    : m_attached_id{attached_id}
    , m_offset_x{offset_x}
    , m_offset_y{offset_y}
    , m_w{w}
    , m_h{h}
	, m_entity_system{entity_system}
    {}

    void print(std::ostream& to) const
    {
    	to << "UseAttachedDirectionalPosition "
    	   << m_offset_x << " "
		   << m_offset_y << " "
		   << m_w << " "
		   << m_h << " ";
    }

    double x() const
    {
    	const Position& attached_position = m_entity_system.template entity_component<Position>(m_attached_id);
    	const Control& attached_control = m_entity_system.template entity_component<Control>(m_attached_id);
		return attached_position.x()
			 + attached_position.w()/2
			 + m_offset_x * (1 - 2*(attached_control.look_dir() == Control::LookDir::LEFT))
			 - m_w/2;
    }

    double y() const
    {
    	const Position& attached_position = m_entity_system.template entity_component<Position>(m_attached_id);
		return attached_position.y()
			 + attached_position.h()/2
			 + m_offset_y
			 - m_h/2;
    }

    double w() const { return m_w; }

    double h() const { return m_h; }

    void set_x(double val) {}
    void set_y(double val) {}
    void set_w(double val) {}
    void set_h(double val) {}

    void mod_x(double val) {}
    void mod_y(double val) {}
    void mod_w(double val) {}
    void mod_h(double val) {}

    EntityID m_attached_id;

private:
    double m_offset_x, m_offset_y, m_w, m_h;
    const EntitySystemT& m_entity_system;
};

template<typename EntitySystemT>
class UseComponentCommand<AttachedDirectionalPosition<EntitySystemT>>
{
public:
    template<typename CommandSystemT, typename AllSystemsT>
    CommandReturnValue operator()(CommandSystemT& command_system, EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	const auto attached_id = command_system.exec_next();
    	const auto offset_x = command_system.exec_next();
    	const auto offset_y = command_system.exec_next();
    	const auto w = command_system.exec_next();
    	const auto h = command_system.exec_next();

    	const EntityID selected_entity = globals(Globals::selected_entity).integer();
		entity_system.set_entity_component(selected_entity, all_systems, rendering_system
									     , AttachedDirectionalPosition<EntitySystemT>
											{ EntityID(attached_id.integer())
											, offset_x.real()
											, offset_y.real()
											, w.real()
											, h.real()
											, entity_system
											}
										  );

    	return CommandReturnValue{0.0};
	}
};

#endif /* COMPONENTS_ATTACHED_DIRECTIONAL_POSITION_H_ */
