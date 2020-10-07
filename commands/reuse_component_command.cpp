/*
 * reuse_component_command.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#include "reuse_component_command.h"
#include <sstream>
#include "../utilities.h"
#include "../components/position.h"
#include "../components/control.h"
#include "../components/movement.h"
#include "../components/collision.h"
#include "../components/interaction.h"
#include "../components/health.h"
#include "../components/visuals.h"
#include "../systems/systems.h"
#include "../systems/entity_system.h"
#include "../command_queue.h"

template<typename T>
void ReuseComponentCommand<T>::execute() const
{
	const auto entity_optional = system<EntitySystem>().resolved_entity(m_source_id);
	if(entity_optional)
	{
		std::stringstream ss;
		ss << entity_optional->component<T>();
		system<CommandQueue>().process_stream(ss, m_renderer);
	}
	else
	{
		//error m_source_id
	}
}

//a hack to make linker happy
template class ReuseComponentCommand<Position>;
template class ReuseComponentCommand<Control>;
template class ReuseComponentCommand<Movement>;
template class ReuseComponentCommand<Collision>;
template class ReuseComponentCommand<Interaction>;
template class ReuseComponentCommand<Health>;
template class ReuseComponentCommand<Visuals>;
