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

template<typename PositionT>
class TiledVisuals
{
public:

	template<typename AnimationAccessorT>
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
	, const AnimationAccessorT& animation_access
	, const EntityID self_id
	, ComponentAccess<const PositionT> position_accessor
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
    , m_position_accessor{std::move(position_accessor)}
    {
			const auto& anim_opt = animation_access(m_animation_id[0]);

			if(anim_opt)
			{
				m_animation_frame_delay = anim_opt->get().frame_delay_ms();
				m_animation_time_max = m_animation_frame_delay*anim_opt->get().frame_count();
			}
			else
			{ /*error m_animation_id[0]*/ }
    }

    template<typename ExtractorF, typename AnimationAccessorT, typename SelfIDObtainerF>
    TiledVisuals
	( ExtractorF&& extract
	, const AnimationAccessorT& animation_access
	, const SelfIDObtainerF& obtain_self_id
	, ComponentAccess<const PositionT> position_accessor
	)
	: TiledVisuals
	  { extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , extract()
	  , animation_access
	  , obtain_self_id()
	  , std::move(position_accessor)
	  }
	{}

	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseTiledVisuals");
    	insert(m_tile_w);
    	insert(m_tile_h);
    	insert(m_animation_id[0]);
    	insert(m_animation_id[1]);
    	insert(m_animation_id[2]);
    	insert(m_animation_id[3]);
    	insert(m_animation_id[4]);
    	insert(m_animation_id[5]);
    	insert(m_animation_id[6]);
    	insert(m_animation_id[7]);
    	insert(m_animation_id[8]);
    }

    void update_animation(const Time time_diff)
    {
    	m_anim_time = (m_anim_time + int(time_diff))%m_animation_time_max;
    }

    AnimationFrame animation_frame(const int rx, const int ry) const
    {
    	return {m_animation_id[anim_index(rx, ry)], m_anim_time/m_animation_frame_delay};
    }

    int repeat_x() const
    {
    	return std::ceil(m_position_accessor(m_self_id).w()/m_tile_w);
    }

    int repeat_y() const
    {
    	return std::ceil(m_position_accessor(m_self_id).h()/m_tile_h);
    }

    VisualLayer layer() const { return m_layer; }
    double look_dir_x() const { return 1.0; }
    double look_dir_y() const { return 1.0; }

    void set_repeat_x(const int val)
    {
    	if(val > 0) m_tile_w = m_position_accessor(m_self_id).w()/val;
    	else
    	{
    		//it will lead to division by 0
    	}
    }

    void set_repeat_y(const int val)
    {
    	if(val > 0)
    		m_tile_h = m_position_accessor(m_self_id).h()/val;
    	else
    	{
    		//it will lead to division by 0
    	}
    }

    void set_layer(const VisualLayer val) { m_layer = val; }

private:
    double m_tile_w, m_tile_h;
    std::array<AnimationID, 9> m_animation_id;
    int m_animation_frame_delay;
    int m_animation_time_max;
    int m_anim_time;
    VisualLayer m_layer;
    EntityID m_self_id;
    ComponentAccess<const PositionT> m_position_accessor;

    int anim_index(const int rx, const int ry) const
    {
    	return (rx > 0) * (1 + (rx==(repeat_x()-1))) + 3*((ry > 0) * (1 + (ry==(repeat_y()-1))));
    }
};

#endif /* COMPONENTS_TILED_VISUALS_H_ */
