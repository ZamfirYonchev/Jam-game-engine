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
class SoundsVariant
{
public:
	using Variant = std::variant<Ts...>;
	Variant variant;

    void update(const Time time_diff) { std::visit([&](auto& snd){ return snd.update(time_diff); }, variant); }

    SoundID id() const { return std::visit([](const auto& snd){ return snd.id(); }, variant); }
    bool changed() const { return std::visit([](const auto& snd){ return snd.changed(); }, variant); }

    double volume() const { return std::visit([](const auto& snd){ return snd.volume(); }, variant); }

    operator bool() const { return variant.index() != 0; }

    template<typename... Tps>
	friend std::ostream& operator<< (std::ostream& out, const SoundsVariant<Tps...>& component)
	{
		print(out, component.variant);
	    out << '\n';
	    return out;
	}
};

#endif /* COMPONENTS_SOUNDS_H_ */
