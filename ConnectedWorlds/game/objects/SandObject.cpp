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
#include "SandObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include "../../zf/zf_sprite.hpp"
SandObject::SandObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::SandObject), count(1)
{
    sprite[0] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand1), sf::Color(255, 255, 0, 255));
    sprite[1] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand2), sf::Color(255, 255, 0, 255));
    sprite[2] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand3), sf::Color(255, 255, 0, 255));
    sprite[3] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand4), sf::Color(255, 255, 0, 255));
    background = zf::setCopyColor(game.getSpecialCharSprite(zf::Fill), sf::Color(100, 100, 40, 255));
}

SandObject::~SandObject()
{
}

void SandObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite[count - 1]);
    if (grabbed)
    {
        window->putSprite_xyb(position.x, position.y, background);
    }
}

bool SandObject::canBeGrabbed() const
{
    return true;
}
