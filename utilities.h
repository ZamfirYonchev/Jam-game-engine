/*
 * utilities.h
 *
 *  Created on: May 24, 2020
 *      Author: zamfi
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "math_ext.h"
#include "types.h"
#include <set>

constexpr double absolute_or_scaled(double val, double scale)
{
	return val*(is_normalized(val)*(scale-1)+1);
}

constexpr HashT hash(const char* str)
{
	HashT hash = 5381;

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

#endif /* UTILITIES_H_ */
