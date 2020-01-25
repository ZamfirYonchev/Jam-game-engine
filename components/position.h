/*
 * position.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef COMPONENTS_POSITION_H_
#define COMPONENTS_POSITION_H_

class Position
{
public:
    virtual ~Position() {}
    virtual double x() const = 0;
    virtual double y() const = 0;
    virtual double w() const = 0;
    virtual double h() const = 0;

    virtual void set_x(double val) = 0;
    virtual void set_y(double val) = 0;
    virtual void set_w(double val) = 0;
    virtual void set_h(double val) = 0;

    virtual void mod_x(double val) = 0;
    virtual void mod_y(double val) = 0;
    virtual void mod_w(double val) = 0;
    virtual void mod_h(double val) = 0;

    static Position* null;
};

#endif /* COMPONENTS_POSITION_H_ */
