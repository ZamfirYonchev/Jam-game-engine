/*
 * null_position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_NULL_POSITION_H_
#define COMPONENTS_NULL_POSITION_H_

#include "position.h"

class NullPosition : public Position
{
public:
    void print(std::ostream& to) const
    {
    	to << "UseNullPosition ";
    }

    double x() const { return 0; }
    double y() const { return 0; }
    double w() const { return 0; }
    double h() const { return 0; }

    void set_x(double val) {}
    void set_y(double val) {}
    void set_w(double val) {}
    void set_h(double val) {}

    void mod_x(double val) {}
    void mod_y(double val) {}
    void mod_w(double val) {}
    void mod_h(double val) {}
};

#endif /* COMPONENTS_NULL_POSITION_H_ */
