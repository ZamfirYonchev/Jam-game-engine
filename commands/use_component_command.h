/*
 * use_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_COMPONENT_COMMAND_H_
#define COMMANDS_USE_COMPONENT_COMMAND_H_

#include "../types.h"
#include "null_command.h"

#include "../components/absolute_position.h"
#include "../components/attached_position.h"
#include "../components/build_position.h"
#include "../components/null_position.h"

#include "../components/chase_ai_control.h"
#include "../components/constant_control.h"
#include "../components/guide_control.h"
#include "../components/input_control.h"
#include "../components/input_select_control.h"
#include "../components/null_control.h"

#include "../components/full_movement.h"
#include "../components/instant_movement.h"
#include "../components/null_movement.h"

#include "../components/basic_collision.h"
#include "../components/damage_collision.h"
#include "../components/null_collision.h"

#include "../components/full_interaction.h"
#include "../components/normal_interaction.h"
#include "../components/trigger_interaction.h"
#include "../components/null_interaction.h"

#include "../components/attached_health.h"
#include "../components/character_health.h"
#include "../components/timed_health.h"
#include "../components/null_health.h"

#include "../components/character_visuals.h"
#include "../components/health_visuals.h"
#include "../components/menu_item_visuals.h"
#include "../components/static_visuals.h"
#include "../components/tiled_visuals.h"
#include "../components/null_visuals.h"

class ResourceSystem;
class InputSystem;
class RenderingSystem;
struct Globals;

template<typename T>
class UseComponentCommand
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename EntitySystemT, typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    const T m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<InputControl<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_self_id = entity_system.previous_entity_id();
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable InputControl<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<ChaseAIControl<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_self_id = entity_system.previous_entity_id();
		m_component.m_target_id = entity_system.resolved_id(m_component.m_target_id);
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable ChaseAIControl<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<GuideControl<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_self_id = entity_system.previous_entity_id();
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable GuideControl<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<HealthVisuals<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_self_id = entity_system.previous_entity_id();
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable HealthVisuals<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<MenuItemVisuals<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_self_id = entity_system.previous_entity_id();
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable MenuItemVisuals<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<BuildPosition<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_attached_id = entity_system.resolved_id(m_component.m_attached_id);
		const Position& builder_pos = entity_system.entity_component(m_component.m_attached_id, (Position*)nullptr);
		m_component.m_self_id = entity_system.previous_entity_id();
		m_component.m_origin_x = builder_pos.x();
		m_component.m_origin_y = builder_pos.y();
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable BuildPosition<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<TiledVisuals<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_self_id = entity_system.previous_entity_id();
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable TiledVisuals<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<AttachedPosition<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_attached_id = entity_system.resolved_id(m_component.m_attached_id);
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable AttachedPosition<EntitySystemT> m_component;
};

template<typename EntitySystemT>
class UseComponentCommand<AttachedHealth<EntitySystemT>>
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	UseComponentCommand(const UseComponentCommand& val) = default;
	UseComponentCommand(UseComponentCommand&& val) noexcept = default;
	UseComponentCommand(UseComponentCommand& val) = default;

    template<typename CommandSystemT, typename AllSystemsT>
    void operator()(EntitySystemT& entity_system, ResourceSystem& resource_system, InputSystem& input_system, CommandSystemT& command_system, RenderingSystem& rendering_system, AllSystemsT& all_systems, Globals& globals) const
	{
		m_component.m_attached_id = entity_system.resolved_id(m_component.m_attached_id);
		entity_system.set_entity_component(entity_system.previous_entity_id(), all_systems, rendering_system, m_component);
	}

private:
    mutable AttachedHealth<EntitySystemT> m_component;
};

#endif /* COMMANDS_USE_COMPONENT_COMMAND_H_ */
