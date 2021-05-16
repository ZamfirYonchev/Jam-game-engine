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
    U& access()
    {
        if constexpr(std::is_same<T, U>::value)
            return t;
        else
            return pack.template access<U>();
    }

    template<typename U>
    const U& access() const
    {
        if constexpr(std::is_same<T, U>::value)
            return t;
        else
            return pack.template access<U>();
    }

    T t;
    TypePack<Ts...> pack;
};

template<typename T>
struct TypePack<T>
{
    template<typename... Us>
    TypePack(Us&&... us) : t{std::forward<Us>(us)...} {}

    template<typename U>
    T& access() { return t; }

    template<typename U>
    const T& access() const { return t; }

    T t;
};

#endif /* TYPE_PACK_H_ */
