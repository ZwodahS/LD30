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
#include "SandWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
SandWorld::SandWorld(Game& game)
    : World(game, World::Type::Sand)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));
    for (int i = 0; i < 10; i++)
    {
        spawnObject(new SandObject(game, *this));
    }
}

SandWorld::~SandWorld()
{
}

void SandWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(70, 70, 50));
    }
    else
    {
        window->clear(sf::Color(70, 70, 0));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(1)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void SandWorld::update(const sf::Time& delta)
{
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::SandObject)
        {
            SandObject* object = static_cast<SandObject*>(block);
            if (object->count == 4)
            {
                block->markedForRemoval = true;
                block->isSpawnElsewhere = true;
                spawnObject(new SandObject(game, *this));
            }
        }
    }
    World::update(delta);
}

bool SandWorld::spawnSand() const
{
    return true;
}
