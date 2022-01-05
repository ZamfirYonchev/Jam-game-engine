/*
 * static_visuals.h
 *
 *  Created on: Nov 11, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_STATIC_VISUALS_H_
#define COMPONENTS_STATIC_VISUALS_H_

#include "visuals_enums.h"

class StaticVisuals
{
public:
	StaticVisuals(const AnimationID anim_id, const int sprite)
	: m_anim_id(anim_id)
	, m_sprite(sprite)
	, m_layer(VisualLayer::FAR_BACKGROUND)
	{}

    template<typename ExtractorF>
	StaticVisuals
	( ExtractorF&& extract
	)
	: StaticVisuals
	  { extract().integer()
	  , extract().integer()
	  }
	{}

	template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseStaticVisuals");
    	insert(m_anim_id);
    	insert(m_sprite);
    }

    void print(std::ostream& to) const
    {
    	to << "UseStaticVisuals "
    	   << m_anim_id << " "
    	   << m_sprite << " ";
    }

    void update_animation(const Time) {}

    AnimationFrame animation_frame(const int, const int) const
    {
    	return {m_anim_id, m_sprite};
    }

    int repeat_x() const { return 1; }
    int repeat_y() const { return 1; }
    VisualLayer layer() const { return m_layer; }

    void set_repeat_x(const int) {}
    void set_repeat_y(const int) {}
    void set_layer(VisualLayer val) { m_layer = val; }

private:
    AnimationID m_anim_id;
    int m_sprite;
    VisualLayer m_layer;
};

#endif /* COMPONENTS_STATIC_VISUALS_H_ */
