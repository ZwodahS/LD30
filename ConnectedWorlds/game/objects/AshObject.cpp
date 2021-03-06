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
#include "AshObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
const sf::Color AshObject::color = sf::Color(255, 50, 50, 255);
const sf::Color AshObject::grabbedColor = sf::Color(255, 150, 150, 255);
AshObject::AshObject(Game& game, World& world, zf::Direction orientation)
    : WorldObject(game, world, ObjectType::AshObject), orientation(orientation)
{
    auto outDirection = getOutputDirections();
    if (outDirection.size() == 2)
    {
        int bitValue = zf::toBit(outDirection[0]) | zf::toBit(outDirection[1]);
        sprite = game.getSpecialCharSprite(zf::Cross[bitValue]);
    }
    sprite.setColor(sf::Color::White);
    normalBackground = game.getSpecialCharSprite(zf::Fill);
    normalBackground.setColor(color);
    grabbedBackground = normalBackground;
    grabbedBackground.setColor(grabbedColor);
}

AshObject::~AshObject()
{
}

void AshObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyb(position.x, position.y, grabbed ? grabbedBackground : normalBackground);
    window->putSprite_xyf(position.x, position.y, sprite);
}

std::vector<zf::Direction> AshObject::getOutputDirections() const
{
    return getOutputDirections(orientation);
}

std::vector<zf::Direction> AshObject::getOutputDirections(zf::Direction orientation)
{
    std::vector<zf::Direction> output;
    if (orientation == zf::Direction::North || orientation == zf::Direction::South 
            || orientation == zf::Direction::East || orientation == zf::Direction::West)
    {
        output.push_back(orientation);
        output.push_back(zf::oppositeOf(orientation));
    }
    else
    {
        int bit = zf::toBit(orientation);
        for (auto direction : zf::AdjacentDirection)
        {
            if (bit & zf::toBit(direction))
            {
                output.push_back(direction);
            }
        }
    }
    return output;
}

std::vector<AshObject*> AshObject::getConnectedBlocks() const
{
    std::vector<AshObject*> connected;
    if (!grabbed && world)
    {
        auto outDirection = getOutputDirections();
        for (auto direction : outDirection)
        {
            auto mod = zf::getModifier(direction);
            auto object = world->getObject(position + mod);
            if (object && object->type == WorldObject::ObjectType::AshObject)
            {
                auto blockObject = static_cast<AshObject*>(object);
                if (blockObject->canConnectFrom(zf::oppositeOf(direction)))
                {
                    connected.push_back(blockObject);
                }
            }
        }
    }
    return connected;
}

bool AshObject::canConnectFrom(zf::Direction direction) const
{
    if (grabbed)
    {
        return false;
    }
    auto outDirections = getOutputDirections();
    return std::find(outDirections.begin(), outDirections.end(), direction) != outDirections.end();
}

bool AshObject::canBeGrabbed() const
{
    return true;
}
