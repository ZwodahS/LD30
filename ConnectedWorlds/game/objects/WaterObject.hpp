/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2013- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 */
#ifndef _GAME_OBJECTS_WATEROBJECT_HPP_
#define _GAME_OBJECTS_WATEROBJECT_HPP_
#include "WorldObject.hpp"
class WaterObject : public WorldObject
{
public:
    WaterObject(Game& game, World& world);
    virtual ~WaterObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
    virtual void update(const sf::Time& delta);
    bool flood;
    int floodMeter; // when it reach 10 it will flood
    virtual bool isPushable() const;
private:
    float timePassed;
    sf::Sprite sprite;
    sf::Sprite background;
};
#endif
