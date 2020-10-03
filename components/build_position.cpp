/*
 * build_position.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: zamfi
 */

#include "build_position.h"
#include "../globals.h"
#include "../math_ext.h"
#include "../commands/select_entity_command.h"
#include "../commands/use_component_command.h"
#include "../components/absolute_position.h"

double BuildPosition::x() const
{
	if(entity_system().entity(m_attached_id))
		return min(m_origin_x, entity_system().entity(m_attached_id)->component<Position>().x());
	else
		return m_origin_x;
}

double BuildPosition::y() const
{
	if(entity_system().entity(m_attached_id))
		return min(m_origin_y, entity_system().entity(m_attached_id)->component<Position>().y());
	else
		return m_origin_y;
}

double BuildPosition::w() const
{
	if(entity_system().entity(m_attached_id))
		return abs(m_origin_x - entity_system().entity(m_attached_id)->component<Position>().x());
	else
		return 0;
}

double BuildPosition::h() const
{
	if(entity_system().entity(m_attached_id))
		return abs(m_origin_y - entity_system().entity(m_attached_id)->component<Position>().y());
	else
		return 0;
}

void BuildPosition::mod_w(double val)
{
	command_queue().push(std::make_unique<SelectEntityCommand>(m_self_id));
	command_queue().push(std::make_unique<UseComponentCommand<AbsolutePosition>>(x(), y(), w(), h()));
}
