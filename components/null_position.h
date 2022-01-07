/*
 * null_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_POSITION_H_
#define COMPONENTS_NULL_POSITION_H_

class NullPosition
{
public:

    template<typename InserterF>
    void obtain(InserterF&& insert) const
	{
    	insert("UseNullPosition");
	}

    double x() const { return 0; }
    double y() const { return 0; }
    double w() const { return 0; }
    double h() const { return 0; }

    void set_x(double) {}
    void set_y(double) {}
    void set_w(double) {}
    void set_h(double) {}

    void mod_x(double) {}
    void mod_y(double) {}
    void mod_w(double) {}
    void mod_h(double) {}
};

#endif /* COMPONENTS_NULL_POSITION_H_ */
