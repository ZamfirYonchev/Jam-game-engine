/*
 * modify_health_command.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: zamfi
 */

#include "modify_health_command.h"
#include "../globals.h"
#include "../math_ext.h"

void ModifyHealthCommand::execute() const
{
	if(entity_system().previous_entity())
	{
		auto& health = entity_system().previous_entity()->component<Health>();

		if(is_negative_zero(m_max_hp))
			health.set_max_hp(0);
		else
			health.set_max_hp(health.max_hp() + m_max_hp);

		if(is_negative_zero(m_hp))
			health.set_hp(0);
		else
			health.set_hp(health.hp() + m_hp);

		if(is_negative_zero(m_hp_change))
			health.set_hp_change(0);
		else
			health.mod_hp_change(m_hp_change);
	}
	else
	{
		//error globals().access_entity_id
	}
}

