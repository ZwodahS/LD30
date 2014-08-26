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
#include "ForestWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
#include "../f_rng.hpp"
ForestWorld::ForestWorld(Game& game)
    : World(game, World::Type::Forest)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));

    spawnObject(new TreeObject(game, *this));
}

ForestWorld::~ForestWorld()
{
}

void ForestWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(50, 70, 50));
    }
    else
    {
        window->clear(sf::Color(0, 70, 0));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(3)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void ForestWorld::update(const sf::Time& delta)
{
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::TreeObject)
        {
            auto object = static_cast<TreeObject*>(block);
            if (object->hasFood())
            {
                block->markedForRemoval = true;
                block->isSpawnElsewhere = true;
                spawnObject(new TreeObject(game, *this));
            }
        }
    }
    World::update(delta);
}
