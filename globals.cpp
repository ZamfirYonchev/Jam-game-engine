/*
 * globals.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "globals.h"

InputHandler& input_handler()
{
	static InputHandler input_handler;
	return input_handler;
}

CommandQueue& command_queue()
{
	static CommandQueue command_queue;
	return command_queue;
}

EntitySystem& entity_system()
{
	static EntitySystem entity_system;
	return entity_system;
}

ResourceSystem& resource_system()
{
	static ResourceSystem resources_system;
	return resources_system;
}

ControlSystem& control_system()
{
	static ControlSystem control_system;
	return control_system;
}

MovementSystem& movement_system()
{
	static MovementSystem movement_system;
	return movement_system;
}

CollisionSystem& collision_system()
{
	static CollisionSystem collision_system;
	return collision_system;
}

DamageSystem& damage_system()
{
	static DamageSystem damage_system;
	return damage_system;
}

RenderingSystem& rendering_system()
{
	static RenderingSystem rendering_system;
	return rendering_system;
}

Globals& globals()
{
	static Globals globals;
	return globals;
}
