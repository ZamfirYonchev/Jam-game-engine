/*
 * reuse_movement_command.cpp
 *
 *  Created on: Jun 28, 2020
 *      Author: zamfi
 */

#include "reuse_movement_command.h"
#include "../globals.h"
#include <sstream>
#include "execute_file_command.h"

void ReuseMovementCommand::execute() const
{
	if(entity_system().entity(m_source_id))
	{
		std::stringstream ss;
		ss << *(entity_system().entity(m_source_id)->movement());
		ExecuteFileCommand::process_stream(ss, m_renderer, true);
	}
	else
	{
		//error m_source_id
	}
}



