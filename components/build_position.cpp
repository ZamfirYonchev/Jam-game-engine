/*
 * build_position.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: zamfi
 */

#include "build_position.h"
#include "../math_ext.h"
#include "../commands/select_entity_command.h"
#include "../commands/use_component_command.h"
#include "../components/absolute_position.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../systems/command_system.h"

double BuildPosition::x() const
{
	return min(m_origin_x, system<EntitySystem>().entity_component<Position>(m_attached_id).x());
}

double BuildPosition::y() const
{
	return min(m_origin_y, system<EntitySystem>().entity_component<Position>(m_attached_id).y());
}

double BuildPosition::w() const
{
	return abs(m_origin_x - system<EntitySystem>().entity_component<Position>(m_attached_id).x());
}

double BuildPosition::h() const
{
	return abs(m_origin_y - system<EntitySystem>().entity_component<Position>(m_attached_id).y());
}

void BuildPosition::mod_w(double val)
{
	system<CommandSystem>().push(std::make_unique<SelectEntityCommand>(m_self_id));
	system<CommandSystem>().push(std::make_unique<UseComponentCommand<AbsolutePosition>>(x(), y(), w(), h()));
}
