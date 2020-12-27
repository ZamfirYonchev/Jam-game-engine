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

class NullSounds;

class Sounds
{
public:
	using Null = NullSounds;

    virtual ~Sounds() {}
    virtual void print(std::ostream& to) const = 0;

    virtual void update(const Time time_diff) = 0;

    virtual SoundID id() const = 0;
    virtual bool changed() const = 0;

    virtual double volume() const = 0;

    static Sounds* null;

    operator bool() const { return this != null; }

    friend std::ostream& operator<< (std::ostream& out, const Sounds& component)
    {
    	component.print(out);
        out << std::endl;
        return out;
    }
};

#endif /* COMPONENTS_SOUNDS_H_ */
