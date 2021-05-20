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

template<typename EntitySystemT>
class SoundSystem : public SystemBase
{
public:
	SoundSystem(EntitySystemT& entity_system, ResourceSystem& resource_system)
	: m_entity_system(entity_system)
	, m_resource_system(resource_system)
	, m_last_paused(false)
	, m_channel_activity_per_entity()
	{}

	void update(const Time time_diff, Globals& globals, std::list<std::pair<EntityID, ProcedureID>>& procedure_calls)
	{
		const int pause_change = globals(Globals::app_paused).boolean() - m_last_paused;
		switch(pause_change)
		{
			case -1 :
			{
				Mix_Resume(-1);
				Mix_ResumeMusic();
				m_last_paused = globals(Globals::app_paused).boolean();
			}
			break;

			case 1 :
			{
				Mix_Pause(-1);
				Mix_PauseMusic();
				m_last_paused = globals(Globals::app_paused).boolean();
			}
			break;

			default:
			break;
		}

		if(m_last_paused == false)
		{
			for(const auto id : entities)
			{
				auto& sounds = m_entity_system.template entity_component<Sounds>(id);
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
								const int channel = Mix_PlayChannel(-1, sound_chunk_optional->get().sound(), sound_chunk_optional->get().repeat());
								channel_activity = {channel, sound_chunk_optional->get().repeat()};
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
    bool m_last_paused;
    std::unordered_map<EntityID, std::pair<int, int>> m_channel_activity_per_entity;
};




#endif /* SYSTEMS_SOUND_SYSTEM_H_ */
