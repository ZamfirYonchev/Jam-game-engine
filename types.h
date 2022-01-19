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

using ResourceID = int32_t;
using AnimationID = ResourceID;
using TextureID = ResourceID;
using ProcedureID = ResourceID;
using SoundID = ResourceID;
using MusicID = ResourceID;
using FontID = ResourceID;

using Time = int32_t;
using GroupID = int;

template<typename T>
using optional_ref = std::optional<std::reference_wrapper<T>>;

template<typename ComponentT>
using ComponentAccess = std::function<ComponentT&(const EntityID id)>;

#endif /* TYPES_H_ */
