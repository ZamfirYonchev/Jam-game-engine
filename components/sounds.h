/*
 * sounds.h
 *
 *  Created on: Nov 22, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_SOUNDS_H_
#define COMPONENTS_SOUNDS_H_
#include "../types.h"
#include <ostream>

#include "component.h"

template<typename... Ts>
class SoundsVariant : public ComponentVariant<Ts...>
{
public:
	using Variant = ComponentVariant<Ts...>;

    void update(const Time time_diff) { std::visit([&](auto& snd){ return snd.update(time_diff); }, Variant::data); }
    SoundID id() const { return std::visit([](const auto& snd){ return snd.id(); }, Variant::data); }
    bool changed() const { return std::visit([](const auto& snd){ return snd.changed(); }, Variant::data); }
    double volume() const { return std::visit([](const auto& snd){ return snd.volume(); }, Variant::data); }
};

#endif /* COMPONENTS_SOUNDS_H_ */
