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

template<typename Variant>
void print(std::ostream& to, const Variant& variant)
{
	std::visit([&](const auto& comp){ comp.print(to); }, variant);
}

template<typename Component>
Component& null()
{
	static Component null_component {};
	return null_component;
}

#endif /* COMPONENTS_COMPONENT_H_ */
