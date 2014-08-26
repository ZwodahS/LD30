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
#include "WorldObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
WorldObject::WorldObject(Game& game, World& world, ObjectType type)
    : type(type), game(game), world(&world), markedForRemoval(false), isSpawnElsewhere(false), grabbed(false)
{
}

WorldObject::~WorldObject()
{
}

void WorldObject::update(const sf::Time& delta)
{
}

bool WorldObject::isPushable() const
{
    return true;
}

bool WorldObject::canBeGrabbed() const
{
    return false;
}

void WorldObject::reset()
{
    markedForRemoval = false;
    isSpawnElsewhere = false;
}

bool WorldObject::grab()
{
    if (!canBeGrabbed())
    {
        return false;
    }
    grabbed = true;
    return grabbed;
}

void WorldObject::drop()
{
    grabbed = false;
}
bool WorldObject::canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const
{
    auto mod = zf::getModifier(direction);
    auto targetPosition = position + mod;
    if (world && world->inRange(targetPosition))
    {
        auto object = world->getObject(targetPosition);
        return !object ? true : object == &grabber ? true : false;
    }
    return false;
}
