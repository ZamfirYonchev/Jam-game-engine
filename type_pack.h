/*
 * type_pack.h
 *
 *  Created on: Oct 18, 2020
 *      Author: zamfi
 */

#ifndef TYPE_PACK_H_
#define TYPE_PACK_H_

#include <type_traits>

template<typename... Ts>
struct TypePack;

template<typename T, typename... Ts>
struct TypePack<T, Ts...>
{
    template<typename... Us>
    TypePack(Us&&... us) : t{std::forward<Us>(us)...}, pack{us...} {}

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

    T t;
    TypePack<Ts...> pack;
};

template<typename T>
struct TypePack<T>
{
    template<typename... Us>
    TypePack(Us&&... us) : t{std::forward<Us>(us)...} {}

    T& access(const T*) { return t; }
    const T& access(const T*) const { return t; }

    T t;
};

#endif /* TYPE_PACK_H_ */
