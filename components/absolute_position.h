/*
 * absolute_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ABSOLUTE_POSITION_H_
#define COMPONENTS_ABSOLUTE_POSITION_H_

#include "position.h"

class AbsolutePosition : public Position
{
public:
	using Base = Position;
    AbsolutePosition(double x, double y, double w, double h)
    : m_x(x), m_y(y), m_width(w), m_height(h) {}
    AbsolutePosition() : AbsolutePosition(0, 0, 0, 0) {}

    void print(std::ostream& to) const
    {
    	to << "UseAbsolutePosition "
    	   << m_x << " "
		   << m_y << " "
		   << m_width << " "
		   << m_height << " ";
    }

    double x() const { return m_x; }
    double y() const { return m_y; }
    double w() const { return m_width; }
    double h() const { return m_height; }

    void set_x(double val) { m_x = val; }
    void set_y(double val) { m_y = val; }
    void set_w(double val) { m_width = val; }
    void set_h(double val) { m_height = val; }

    void mod_x(double val) { m_x += val; }
    void mod_y(double val) { m_y += val; }
    void mod_w(double val) { m_width += val; }
    void mod_h(double val) { m_height += val; }

private:
    double m_x, m_y, m_width, m_height;
};

#endif /* COMPONENTS_ABSOLUTE_POSITION_H_ */
