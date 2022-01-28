/*
 * static_animation_visuals.h
 *
 *  Created on: Jan 17, 2021
 *      Author: zamfi
 */

#ifndef COMPONENTS_ANIMATION_VISUALS_H_
#define COMPONENTS_ANIMATION_VISUALS_H_

#include "visuals_enums.h"

class AnimationVisuals
{
public:
    template<typename ExtractorF, typename AnimationAccessorT>
	AnimationVisuals
	( ExtractorF&& extract
	, const AnimationAccessorT& animation_access
	)
	: m_anim_id{extract()}
	, m_layer{VisualLayer::FAR_BACKGROUND}
	, m_anim_frame_delay{1}
	, m_anim_time{0}
	, m_anim_time_max{1}
	{
		const auto& anim_opt = animation_access(m_anim_id);

		if(anim_opt)
		{
			m_anim_frame_delay = anim_opt->get().frame_delay_ms();
			m_anim_time_max = m_anim_frame_delay*anim_opt->get().frame_count();
		}
		else
		{
			//error anim_id
		}
	}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseAnimationVisuals");
    	insert(m_anim_id);
    }

    void update_animation(const Time time_diff)
    {
    	m_anim_time = (m_anim_time+int(time_diff))%m_anim_time_max;
    }

    AnimationFrame animation_frame(const int, const int) const
    {
    	return {m_anim_id, m_anim_time/m_anim_frame_delay};
    }

    AnimationID animation_id(const int, const int) const { return m_anim_id; }
    int repeat_x() const { return 1; }
    int repeat_y() const { return 1; }
    VisualLayer layer() const { return m_layer; }
    double look_dir_x() const { return 0.0; }
    double look_dir_y() const { return 0.0; }

    void set_repeat_x(const int) {}
    void set_repeat_y(const int) {}
    void set_layer(const VisualLayer val) { m_layer = val; }


private:
    AnimationID m_anim_id;
    VisualLayer m_layer;
    int m_anim_frame_delay;
    int m_anim_time;
    int m_anim_time_max;
};

#endif /* COMPONENTS_ANIMATION_VISUALS_H_ */
