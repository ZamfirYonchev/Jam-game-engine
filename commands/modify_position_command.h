/*
 * modify_position_command.h
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#ifndef COMMANDS_MODIFY_POSITION_COMMAND_H_
#define COMMANDS_MODIFY_POSITION_COMMAND_H_

#include "../math_ext.h"
#include "../components/position.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

class ModifyPositionCommand
{
public:
	ModifyPositionCommand(double x, double y, double w, double h)
	: m_x(x)
	, m_y(y)
	, m_w(w)
	, m_h(h)
	{}

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
    	Position& position = entity_system.entity_component(entity_system.previous_entity_id(), (Position*)nullptr);

		if(position)
		{
			if(is_negative_zero(m_x))
				position.set_x(m_x);
			else
				position.mod_x(m_x);

			if(is_negative_zero(m_y))
				position.set_y(m_y);
			else
				position.mod_y(m_y);

			if(is_negative_zero(m_w))
				position.set_w(m_w);
			else
				position.mod_w(m_w);

			if(is_negative_zero(m_h))
				position.set_h(m_h);
			else
				position.mod_h(m_h);
		}
		else
		{
			//error entity_system.previous_entity_id()
		}
	}

private:
    double m_x, m_y, m_w, m_h;
};


#endif /* COMMANDS_MODIFY_POSITION_COMMAND_H_ */
