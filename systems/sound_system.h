/*
 * sound_system.h
 *
 *  Created on: Nov 24, 2020
 *      Author: zamfi
 */

#ifndef SYSTEMS_SOUND_SYSTEM_H_
#define SYSTEMS_SOUND_SYSTEM_H_

#include "system_base.h"
#include "resource_system.h"
#include <list>
#include "../types.h"
#include "../components/sounds.h"
#include <vector>
#include "../globals.h"

template<typename EntitySystemT>
class SoundSystem : public SystemBase
{
public:
	SoundSystem(EntitySystemT& entity_system, ResourceSystem& resource_system)
	: m_entity_system(entity_system)
	, m_resource_system(resource_system)
	, m_channel_activity_per_entity()
	{}

	void update(const Time time_diff, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
	{
		for(const auto id : entities)
		{
			auto& sounds = m_entity_system.entity_component(id, (Sounds*)nullptr);
	    	if(sounds)
	    	{
	    		sounds.update(time_diff);

	    		if(sounds.changed())
	    		{
	    			auto& channel_activity = m_channel_activity_per_entity[id];
	    			if(channel_activity.second == -1)
					{
	    				Mix_HaltChannel(channel_activity.first);
	    				channel_activity.second = 0;
					}

					if(sounds.id() >= 0)
					{
						const auto& sound_chunk_optional = m_resource_system.sound(sounds.id());

						if(sound_chunk_optional)
						{
							const int channel = Mix_PlayChannel(-1, sound_chunk_optional->sound(), sound_chunk_optional->repeat());
							channel_activity = {channel, sound_chunk_optional->repeat()};
						}
						else
						{
							//error sounds.sound_id()
						}
	    			}
	    		}
	    	}
	    	else
	    	{
	    		//error *it
	    	}
		}
	}

    template<typename T>
    void component_updated(const T& component, const EntityID id, const int8_t change)
    {
    	if constexpr(std::is_same<T, Sounds>::value)
		{
    		if(change < 0)
    			remove_id(id);
    		else if(change > 0)
    			add_id(id);
		}
    }

private:
    EntitySystemT& m_entity_system;
    ResourceSystem& m_resource_system;
    std::unordered_map<EntityID, std::pair<int, int>> m_channel_activity_per_entity;
};




#endif /* SYSTEMS_SOUND_SYSTEM_H_ */
