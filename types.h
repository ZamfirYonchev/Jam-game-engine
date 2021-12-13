/*
 * types.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <cinttypes>
#include <optional>
#include <functional>

using HashT = uint64_t;

using EntityID = int32_t;
using AnimationID = int32_t;
using TextureID = int32_t;
using ProcedureID = int32_t;
using SoundID = int32_t;
using MusicID = int32_t;
using FontID = int32_t;
using Time = int32_t;
using GroupID = int;

template<typename T>
using optional_ref = std::optional<std::reference_wrapper<T>>;

template<typename ComponentT>
using ComponentAccess = std::function<ComponentT&(const EntityID id)>;

#endif /* TYPES_H_ */
