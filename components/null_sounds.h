/*
 * null_sounds.h
 *
 *  Created on: Nov 25, 2020
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_SOUNDS_H_
#define COMPONENTS_NULL_SOUNDS_H_

class NullSounds
{
public:
	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseNullSounds");
    }

    void print(std::ostream& to) const
    {
    	to << "UseNullSounds ";
    }

    void update(const Time) {}
    bool changed() const { return false; }
    SoundID id() const { return -1; }
    double volume() const { return 0; }
};

#endif /* COMPONENTS_NULL_SOUNDS_H_ */
