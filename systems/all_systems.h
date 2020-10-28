/*
 * all_systems.h
 *
 *  Created on: Oct 17, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_ALL_SYSTEMS_H_
#define SYSTEMS_ALL_SYSTEMS_H_

#include "../type_pack.h"
#include "../types.h"
#include <list>
#include <utility>

template<typename... Ts>
struct AllSystems
{
	TypePack<Ts...> pack;

	template<typename EntitySystemT>
	AllSystems(EntitySystemT& entity_system) : pack{entity_system} {}

	void clear()
	{
		((void)pack.access((Ts*)nullptr).clear(), ...);
	}

	template<typename ComponentT>
	void component_updated(const ComponentT& component, const EntityID id, const int8_t change)
	{
		((void)pack.access((Ts*)nullptr).component_updated(component, id, change), ...);
	}

	template<typename EntitySystemT>
	void update(const Time time_diff, EntitySystemT& entity_system, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
	{
		((void)pack.access((Ts*)nullptr).update(time_diff, entity_system, procedure_calls), ...);
	}

	void remove_id(const EntityID id)
	{
		((void)pack.access((Ts*)nullptr).remove_id(id), ...);
	}
};

#endif /* SYSTEMS_ALL_SYSTEMS_H_ */
