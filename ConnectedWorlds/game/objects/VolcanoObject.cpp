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
#include "VolcanoObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
VolcanoObject::VolcanoObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::VolcanoObject), time(game.balance.Volcano_EruptFrequency), blocked(false)
{
    background = game.getSpecialCharSprite(zf::Fill);
    background.setColor(sf::Color(200, 50, 50));
    sprite = game.getSpecialCharSprite(game.Special_Volcano);
}

VolcanoObject::~VolcanoObject()
{
}

void VolcanoObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyfb(position.x, position.y, sprite, background);
}

bool VolcanoObject::isPushable() const
{
    return false;
}

bool VolcanoObject::canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const
{
    return false;
}

bool VolcanoObject::canBeGrabbed() const
{
    return false;
}
