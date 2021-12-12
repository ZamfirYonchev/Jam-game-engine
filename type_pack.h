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
struct TypePack {};

template<typename T, typename... Ts>
struct TypePack<T, Ts...>
{
	TypePack() = default;

    template<typename U, typename... Us>
    TypePack(U&& u, Us&&... us) : t{std::forward<U>(u)}, pack{std::forward<Us>(us)...} {}

    template<typename U>
    U& access()
    {
    	using D = std::decay_t<U>;
        if constexpr(std::is_same<T, D>::value)
            return t;
        else
            return pack.template access<D>();
    }

    template<typename U>
    const U& access() const
    {
    	using D = std::decay_t<U>;
        if constexpr(std::is_same<T, D>::value)
            return t;
        else
            return pack.template access<D>();
    }

    T t;
    TypePack<Ts...> pack;
};

template<typename T>
struct TypePack<T>
{
	TypePack() = default;

	template<typename U>
    TypePack(U&& u) : t{std::forward<U>(u)} {}

    template<typename U>
    T& access() { return t; }

    template<typename U>
    const T& access() const { return t; }

    T t;
};

#endif /* TYPE_PACK_H_ */
