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
using FontID = int32_t;
using Time = int32_t;

using AbsEntityID = std::size_t;
using AbsSpritesheetID = std::size_t;
using AbsTextureID = std::size_t;
using AbsProcedureID = std::size_t;
using AbsSoundID = std::size_t;
using AbsFontID = std::size_t;
using AbsTime = uint32_t;


#endif /* TYPES_H_ */
