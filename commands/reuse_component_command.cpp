/*
 * reuse_component_command.cpp
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#include "reuse_component_command.h"
#include "../globals.h"
#include <sstream>
#include "execute_file_command.h"
#include "../components/position.h"
#include "../components/control.h"
#include "../components/movement.h"
#include "../components/collision.h"
#include "../components/interaction.h"
#include "../components/health.h"
#include "../components/visuals.h"

template<typename T>
void ReuseComponentCommand<T>::execute() const
{
	if(entity_system().entity(m_source_id))
	{
		std::stringstream ss;
		ss << entity_system().entity(m_source_id)->component<T>();
		ExecuteFileCommand::process_stream(ss, m_renderer, true);
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
