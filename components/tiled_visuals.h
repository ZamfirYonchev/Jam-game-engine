/*
 * tiled_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_TILED_VISUALS_H_
#define COMPONENTS_TILED_VISUALS_H_

#include "visuals_enums.h"
#include <array>
#include "../types.h"
#include "../math_ext.h"
#include "../systems/resource_system.h"

class Position;

class TiledVisuals
{
public:
	TiledVisuals
	( const double tile_w
	, const double tile_h
	, const AnimationID bottom_left_anim_id
	, const AnimationID bottom_center_anim_id
	, const AnimationID bottom_right_anim_id
	, const AnimationID middle_left_anim_id
	, const AnimationID middle_center_anim_id
	, const AnimationID middle_right_anim_id
	, const AnimationID top_left_anim_id
	, const AnimationID top_center_anim_id
	, const AnimationID top_right_anim_id
	, const ResourceSystem& resource_system
	, const EntityID self_id
	, const ComponentAccess<const Position>& position_accessor
	)
    : m_tile_w{tile_w}
    , m_tile_h{tile_h}
    , m_animation_id
		{ bottom_left_anim_id
		, bottom_center_anim_id
		, bottom_right_anim_id
		, middle_left_anim_id
		, middle_center_anim_id
		, middle_right_anim_id
		, top_left_anim_id
		, top_center_anim_id
		, top_right_anim_id
		}
    , m_animation_frame_delay{1}
    , m_animation_time_max{1}
	, m_anim_time{0}
	, m_layer{VisualLayer::ACTION}
    , m_self_id{self_id}
    , m_position_accessor{position_accessor}
    {
			const auto& anim_opt = resource_system.animation(m_animation_id[0]);

			if(anim_opt)
			{
				m_animation_frame_delay = anim_opt->get().frame_delay_ms();
				m_animation_time_max = m_animation_frame_delay*anim_opt->get().frame_count();
			}
			else
			{ /*error m_animation_id[0]*/ }
    }

    template<typename ExtractorF, typename SelfIDObtainerF>
    TiledVisuals
	( ExtractorF&& extract
	, const ResourceSystem& resource_system
	, SelfIDObtainerF&& obtain_self_id
	, const ComponentAccess<const Position>& position_accessor
	)
	: TiledVisuals
	  { extract().real()
	  , extract().real()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , extract().integer()
	  , resource_system
	  , obtain_self_id()
	  , position_accessor
	  }
	{}

    void print(std::ostream& to) const
    {
    	to << "UseTiledVisuals "
    	   << m_tile_w << " "
    	   << m_tile_h << " "
    	   << m_animation_id[0] << " "
    	   << m_animation_id[1] << " "
    	   << m_animation_id[2] << " "
    	   << m_animation_id[3] << " "
    	   << m_animation_id[4] << " "
    	   << m_animation_id[5] << " "
    	   << m_animation_id[6] << " "
    	   << m_animation_id[7] << " "
    	   << m_animation_id[8] << " ";
    }

    void update_animation(const Time time_diff)
    {
    	m_anim_time = (m_anim_time + int(time_diff))%m_animation_time_max;
    }

    AnimationFrame animation_frame(const int rx, const int ry) const
    {
    	return {m_animation_id[anim_index(rx, ry)], m_anim_time/m_animation_frame_delay};
    }

    int repeat_x() const;
    int repeat_y() const;
    VisualLayer layer() const { return m_layer; }
    void set_repeat_x(const int val);
    void set_repeat_y(const int val);
    void set_layer(const VisualLayer val) { m_layer = val; }

private:
    double m_tile_w, m_tile_h;
    std::array<AnimationID, 9> m_animation_id;
    int m_animation_frame_delay;
    int m_animation_time_max;
    int m_anim_time;
    VisualLayer m_layer;
    EntityID m_self_id;
    ComponentAccess<const Position> m_position_accessor;

    int anim_index(const int rx, const int ry) const
    {
    	return (rx > 0) * (1 + (rx==(repeat_x()-1))) + 3*((ry > 0) * (1 + (ry==(repeat_y()-1))));
    }
};

#endif /* COMPONENTS_TILED_VISUALS_H_ */
