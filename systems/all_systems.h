/*
 * all_systems.h
 *
 *  Created on: Oct 17, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_ALL_SYSTEMS_H_
#define SYSTEMS_ALL_SYSTEMS_H_

#include "../ref_pack.h"
#include "../types.h"
#include "../globals.h"
#include <list>
#include <utility>

template<typename... Ts>
struct AllSystems
{
	RefPack<Ts...> pack;

	AllSystems(Ts&... ts) : pack{ts...} {}

	void clear()
	{
		((void)pack.template access<Ts>().clear(), ...);
	}

	template<typename ComponentT>
	void component_updated(const ComponentT& component, const EntityID id, const int8_t change)
	{
		((void)pack.template access<Ts>().component_updated(component, id, change), ...);
	}

	void update(const Time time_diff)
	{
		((void)pack.template access<Ts>().update(time_diff), ...);
	}

	void remove_id(const EntityID id)
	{
		((void)pack.template access<Ts>().remove_id(id), ...);
	}
};

#endif /* SYSTEMS_ALL_SYSTEMS_H_ */
