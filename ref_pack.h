/*
 * ref_pack.h
 *
 *  Created on: Nov 24, 2020
 *      Author: zamfi
 */

#ifndef REF_PACK_H_
#define REF_PACK_H_

#include <type_traits>

template<typename... Ts>
struct RefPack;

template<typename T, typename... Ts>
struct RefPack<T, Ts...>
{
    RefPack(T& _t, Ts&... _ts) : t{_t}, pack{_ts...} {}

    template<typename U>
    U& access(const U* ptr)
    {
        if constexpr(std::is_same<T, U>::value)
            return t;
        else
            return pack.access(ptr);
    }

    template<typename U>
    const U& access(const U* ptr) const
    {
        if constexpr(std::is_same<T, U>::value)
            return t;
        else
            return pack.access(ptr);
    }

    T& t;
    RefPack<Ts...> pack;
};

template<typename T>
struct RefPack<T>
{
    RefPack(T& _t) : t{_t} {}

    T& access(const T*) { return t; }
    const T& access(const T*) const { return t; }

    T& t;
};

#endif /* REF_PACK_H_ */
