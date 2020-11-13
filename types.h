/*
 * types.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <cinttypes>

template<typename T>
class ExplicitAlias
{
    public:
	using Type = T;
    explicit constexpr ExplicitAlias(const T val) noexcept : m_value{val} {}
    explicit constexpr ExplicitAlias() noexcept : m_value{} {}
    constexpr operator T() const noexcept { return m_value; }

    private:
    T m_value;
};

using EntityID = int32_t;
using SpritesheetID = int32_t;
using TextureID = int32_t;
using ProcedureID = int32_t;
using SoundID = int32_t;
using MusicID = int32_t;
using FontID = int32_t;
using Time = int32_t;

#endif /* TYPES_H_ */
