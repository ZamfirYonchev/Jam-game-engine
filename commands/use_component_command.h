/*
 * use_component_command.h
 *
 *  Created on: Jul 1, 2020
 *      Author: zamfi
 */

#ifndef COMMANDS_USE_COMPONENT_COMMAND_H_
#define COMMANDS_USE_COMPONENT_COMMAND_H_

#include "command.h"
#include "../types.h"
#include "null_command.h"
#include "../components/input_control.h"
#include "../components/input_select_control.h"
#include "../components/chase_ai_control.h"
#include "../components/guide_control.h"
#include "../components/health_visuals.h"
#include "../components/menu_item_visuals.h"
#include "../components/build_position.h"
#include "../components/tiled_visuals.h"
#include "../components/attached_position.h"
#include "../components/attached_health.h"

template<typename T>
class UseComponentCommand : public Command
{
public:
	template<typename... Args>
	UseComponentCommand(Args&&... args)
	: m_component(std::forward<Args>(args)...) {}

	void execute() const;
    std::unique_ptr<Command> clone()
    {
    	return std::make_unique<UseComponentCommand<T>>(m_component);
    }

private:
    T m_component;
};

template<>
class UseComponentCommand<InputControl> : public Command
{
public:
	UseComponentCommand(const ProcedureID proc_id, const double proc_cooldown, bool stability_control)
	: m_proc_id(proc_id)
	, m_proc_cooldown(proc_cooldown)
	, m_stability_control(stability_control)
	{}

	void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<InputControl>>(m_proc_id, m_proc_cooldown, m_stability_control); }

private:
    ProcedureID m_proc_id;
    double m_proc_cooldown;
    bool m_stability_control;
};

template<>
class UseComponentCommand<InputSelectControl> : public Command
{
public:
	UseComponentCommand<InputSelectControl>(int select, int max, ProcedureID proc_id)
	: m_select(select)
	, m_max(max)
	, m_proc_id(proc_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<InputSelectControl>>(m_select, m_max, m_proc_id); }
private:
    int m_select;
    int m_max;
    ProcedureID m_proc_id;
};

template<>
class UseComponentCommand<ChaseAIControl> : public Command
{
public:
	UseComponentCommand<ChaseAIControl>(EntityID target_id, ProcedureID attack_id, double attack_cooldown, double attack_range)
	: m_target_id(target_id)
	, m_attack_id(attack_id)
	, m_attack_cooldown(attack_cooldown)
	, m_attack_range(attack_range)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<ChaseAIControl>>(m_target_id, m_attack_id, m_attack_cooldown, m_attack_range); }

private:
    EntityID m_target_id;
    ProcedureID m_attack_id;
    double m_attack_cooldown, m_attack_range;
};

template<>
class UseComponentCommand<GuideControl> : public Command
{
public:
	UseComponentCommand<GuideControl>(EntityID target_id, double range)
	: m_target_id(target_id)
	, m_range(range)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<GuideControl>>(m_target_id, m_range); }
private:
    EntityID m_target_id;
    double m_range;
};

template<>
class UseComponentCommand<HealthVisuals> : public Command
{
public:
	UseComponentCommand<HealthVisuals>(SpritesheetID spr_id, uint16_t repeat_x)
	: m_spr_id(spr_id)
	, m_repeat_x(repeat_x)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<HealthVisuals>>(m_spr_id, m_repeat_x); }
private:
    SpritesheetID m_spr_id;
    uint16_t m_repeat_x;
};

template<>
class UseComponentCommand<MenuItemVisuals> : public Command
{
public:
	UseComponentCommand<MenuItemVisuals>(SpritesheetID spr_id)
	: m_spr_id(spr_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<MenuItemVisuals>>(m_spr_id); }
private:
    SpritesheetID m_spr_id;
};

template<>
class UseComponentCommand<BuildPosition> : public Command
{
public:
	UseComponentCommand<BuildPosition>(EntityID builder_id)
	: m_builder_id(builder_id)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<BuildPosition>>(m_builder_id); }
private:
    SpritesheetID m_builder_id;
};

template<>
class UseComponentCommand<TiledVisuals> : public Command
{
public:
	UseComponentCommand<TiledVisuals>(const SpritesheetID spr_id, const double tile_w, const double tile_h)
	: m_spr_id(spr_id)
	, m_tile_w(tile_w)
	, m_tile_h(tile_h)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<TiledVisuals>>(m_spr_id, m_tile_w, m_tile_h); }
private:
    SpritesheetID m_spr_id;
    double m_tile_w;
    double m_tile_h;
};

template<>
class UseComponentCommand<AttachedPosition> : public Command
{
public:
	UseComponentCommand<AttachedPosition>(const EntityID attached_id, const double offset_x, const double offset_y, const double offset_w, const double offset_h)
	: m_attached_id(attached_id)
	, m_offset_x(offset_x)
	, m_offset_y(offset_y)
	, m_offset_w(offset_w)
	, m_offset_h(offset_h)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<AttachedPosition>>(m_attached_id, m_offset_x, m_offset_y, m_offset_w, m_offset_h); }
private:
    EntityID m_attached_id;
    double m_offset_x, m_offset_y, m_offset_w, m_offset_h;
};

template<>
class UseComponentCommand<AttachedHealth> : public Command
{
public:
	UseComponentCommand<AttachedHealth>(const EntityID attached_id, const double offset_hp, const double offset_max_hp)
	: m_attached_id(attached_id)
	, m_offset_hp(offset_hp)
	, m_offset_max_hp(offset_max_hp)
	{}

    void execute() const;
    std::unique_ptr<Command> clone() { return std::make_unique<UseComponentCommand<AttachedHealth>>(m_attached_id, m_offset_hp, m_offset_max_hp); }
private:
    EntityID m_attached_id;
    double m_offset_hp, m_offset_max_hp;
};

#endif /* COMMANDS_USE_COMPONENT_COMMAND_H_ */
