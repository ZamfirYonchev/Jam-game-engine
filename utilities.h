/*
 * utilities.h
 *
 *  Created on: May 24, 2020
 *      Author: zamfi
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "globals.h"
#include "math_ext.h"
#include <set>

constexpr double absolute_or_scaled(double val, double scale)
{
	return val*(is_normalized(val)*(scale-1)+1);
}

constexpr unsigned long hash(const char* str)
{
    unsigned long hash = 5381;

    while (int c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

template <class T, class Comp, class Alloc, class Predicate>
void discard_if(std::set<T, Comp, Alloc>& c, Predicate pred) {
    for (auto it{std::begin(c)}, end{std::end(c)}; it != end; ) {
        if (pred(*it)) {
            it = c.erase(it);
        }
        else {
            ++it;
        }
    }
}

template<typename T>
constexpr bool is_null_component(const T& component)
{
	return &component == T::null;
}

#endif /* UTILITIES_H_ */
