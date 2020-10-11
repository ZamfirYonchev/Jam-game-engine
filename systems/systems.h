/*
 * systems.h
 *
 *  Created on: Oct 7, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_SYSTEMS_H_
#define SYSTEMS_SYSTEMS_H_

#include "../types.h"
#include <initializer_list>

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
		(void) std::initializer_list<int>{ (system<SystemTs>().clear(), 0)...};
	}

	template<typename ComponentT>
	static void component_updated(const ComponentT& c)
	{
		//todo
	}

	static void update(const Time time_diff)
	{
		(void) std::initializer_list<int>{ (system<SystemTs>().update(time_diff), 0)...};
	}

	static void remove_id(const EntityID id)
	{
		(void) std::initializer_list<int>{ (system<SystemTs>().remove_id(id), 0)...};
	}
};

#endif /* SYSTEMS_SYSTEMS_H_ */
