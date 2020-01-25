/*
 * attached_position.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#include "attached_position.h"
#include "../globals.h"

double AttachedPosition::x() const
{
    return globals.entity_system.entity(m_attached_id)->position()->x() + m_offset_x;
}

double AttachedPosition::y() const
{
    return globals.entity_system.entity(m_attached_id)->position()->y() + m_offset_y;
}

double AttachedPosition::w() const
{
    return globals.entity_system.entity(m_attached_id)->position()->w() + m_offset_w;
}

double AttachedPosition::h() const
{
    return globals.entity_system.entity(m_attached_id)->position()->h() + m_offset_h;
}

