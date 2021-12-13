/*
 * absolute_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_ABSOLUTE_POSITION_H_
#define COMPONENTS_ABSOLUTE_POSITION_H_

class AbsolutePosition
{
public:
    AbsolutePosition(const double x, const double y, const double w, const double h)
    : m_x(x), m_y(y), m_width(w), m_height(h) {}
    AbsolutePosition() : AbsolutePosition(0, 0, 0, 0) {}

    template<typename ExtractorF>
    AbsolutePosition(ExtractorF&& extract)
    : AbsolutePosition
	  { extract().real()
      , extract().real()
	  , extract().real()
	  , extract().real()
	  }
    {}

    template<typename InserterF>
    void obtain(InserterF&& insert) const
    {
    	insert("UseAbsolutePosition");
    	insert(m_x);
    	insert(m_y);
    	insert(m_width);
    	insert(m_height);
    }

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
