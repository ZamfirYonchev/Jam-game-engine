/*
 * attached_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ATTACHED_POSITION_H_
#define COMPONENTS_ATTACHED_POSITION_H_

#include "position.h"
#include "../types.h"

class AttachedPosition : public Position
{
public:
    AttachedPosition(EntityID attached_id, double offset_x, double offset_y, double offset_w, double offset_h)
    : m_attached_id(attached_id)
    , m_offset_x(offset_x)
    , m_offset_y(offset_y)
    , m_offset_w(offset_w)
    , m_offset_h(offset_h)
    {}

    AttachedPosition(EntityID attached_id)
    : AttachedPosition(attached_id, 0, 0, 0, 0) {}

    double x() const;
    double y() const;
    double w() const;
    double h() const;

    void set_x(double val) {}
    void set_y(double val) {}
    void set_w(double val) {}
    void set_h(double val) {}

    void mod_x(double val) { m_offset_x += val; }
    void mod_y(double val) { m_offset_y += val; }
    void mod_w(double val) { m_offset_w += val; }
    void mod_h(double val) { m_offset_h += val; }

private:
    EntityID m_attached_id;
    double m_offset_x, m_offset_y, m_offset_w, m_offset_h;
};


#endif /* COMPONENTS_ATTACHED_POSITION_H_ */
