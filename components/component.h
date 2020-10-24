/*
 * component.h
 *
 *  Created on: Oct 3, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_COMPONENT_H_
#define COMPONENTS_COMPONENT_H_

#include <memory>

struct free_if_not_nullobj
{
	template<typename T>
	void operator()(T* p){ if(p != T::null) delete p; p = T::null; };
};

template<typename T>
using unique_component_ptr = std::unique_ptr<T, free_if_not_nullobj>;


template<typename T, typename... Args>
inline unique_component_ptr<typename T::Base> make_unique_component(Args&&... args)
{
	using BaseT = typename T::Base;
	using NullT = typename BaseT::Null;

	if constexpr(std::is_same<T, NullT>::value)
		return unique_component_ptr<BaseT>{T::null};
	else
		return unique_component_ptr<BaseT>{new T{std::forward<Args>(args)...}};
}

#endif /* COMPONENTS_COMPONENT_H_ */
