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
		[[maybe_unused]] const auto dummy = { (system<SystemTs>().clear(), 0)...};
	}

	static void update(const Time time_diff)
	{
		[[maybe_unused]] const auto dummy = { (system<SystemTs>().update(time_diff), 0)...};
	}
};

#endif /* SYSTEMS_SYSTEMS_H_ */
