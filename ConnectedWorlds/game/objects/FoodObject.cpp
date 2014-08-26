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
#include "FoodObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
FoodObject::FoodObject(Game& game, World& world)
    : WorldObject(game, world, WorldObject::ObjectType::FoodObject)
{
    sprite = zf::setCopyColor(game.getCharSprite('%'), sf::Color(0, 255, 0));
    grabbedBackground = zf::setCopyColor(game.getSpecialCharSprite(zf::Fill), sf::Color(50, 100, 50, 255));
}

FoodObject::~FoodObject()
{
}

void FoodObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    if (grabbed)
    {
        window->putSprite_xyfb(position.x, position.y, sprite, grabbedBackground);
    }
    else
    {
        window->putSprite_xyf(position.x, position.y, sprite);
    }
}
