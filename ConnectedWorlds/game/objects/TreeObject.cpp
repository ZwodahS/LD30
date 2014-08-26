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
#include "TreeObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"

TreeObject::TreeObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::TreeObject), currentStage(0)
{
    background = game.getSpecialCharSprite(zf::Fill);
    background.setColor(sf::Color(50, 120, 50));
    sprite[0] = game.getCharSprite('.');
    sprite[1] = game.getCharSprite(',');
    sprite[2] = game.getCharSprite('i');
    sprite[3] = game.getCharSprite('t');
    sprite[4] = game.getCharSprite('T');
    for (int i = 0; i < STAGES; i++)
    {
        sprite[i].setColor(sf::Color(0, 255, 0, 255));
    }
}

TreeObject::~TreeObject()
{
}

void TreeObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite[currentStage >= STAGES ? STAGES - 1 : currentStage]);
    if (grabbed)
    {
        window->putSprite_xyb(position.x, position.y, background);
    }
}

bool TreeObject::canBeGrabbed() const
{
    return true;
}

bool TreeObject::grow()
{
    if (currentStage == STAGES)
    {
        return false;
    }
    currentStage++;
    return true;
}

bool TreeObject::hasFood() const
{
    return currentStage == STAGES;
}
