/*
 * systems.h
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_SYSTEMS_H_
#define SYSTEMS_SYSTEMS_H_

#include "../types.h"

template<typename SystemT>
inline SystemT& system()
{
	static SystemT system;
	return system;
}

template<typename... SystemTs>
struct Systems
{
	static void clear()
	{
		((void)system<SystemTs>().clear(), ...);
	}

	template<typename ComponentT>
	static void component_updated(const ComponentT& component, const EntityID id)
	{
		((void)system<SystemTs>().component_updated(component, id), ...);
	}

	static void update(const Time time_diff)
	{
		((void)system<SystemTs>().update(time_diff), ...);
	}

	static void remove_id(const EntityID id)
	{
		((void)system<SystemTs>().remove_id(id), ...);
	}
};

#endif /* SYSTEMS_SYSTEMS_H_ */
