/*
 * component.h
 *
 *  Created on: Oct 3, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_COMPONENT_H_
#define COMPONENTS_COMPONENT_H_

#include <memory>
#include <variant>
#include <ostream>

template<typename... Ts>
class ComponentVariant
{
public:
	std::variant<Ts...> data;

    template<typename InserterF>
    void obtain(InserterF&& inserter) const
	{
		std::visit([&](const auto& component){ return component.obtain(std::forward<InserterF>(inserter)); }, data);
	}

    operator bool() const { return data.index() != 0; }
};

template<typename Component>
Component& null()
{
	static Component null_component {};
	return null_component;
}

#endif /* COMPONENTS_COMPONENT_H_ */
