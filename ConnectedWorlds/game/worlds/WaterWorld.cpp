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
#include "WaterWorld.hpp"
#include "../Game.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
WaterWorld::WaterWorld(Game& game)
    : World(game, World::Type::Water)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
        for (int y = game.WorldSize.y - 3; y < game.WorldSize.y; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
    }
    for (int x = game.WorldSize.x - 3; x < game.WorldSize.x; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
        for (int y = game.WorldSize.y - 3; y < game.WorldSize.y; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
    }
}

WaterWorld::~WaterWorld()
{
}

void WaterWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(50, 50, 70));
    }
    else
    {
        window->clear(sf::Color(0, 0, 50));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(2)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void WaterWorld::update(const sf::Time& delta)
{
    std::vector<WaterObject*> flooded;
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::WaterObject)
        {
            WaterObject* object = static_cast<WaterObject*>(block);
            if (object->floodMeter >= 10)
            {
                object->floodMeter = 0;
                flooded.push_back(object);
            }
        }
    }
    for (auto object : flooded)
    {
        for (auto direction : zf::AdjacentDirection)
        {
            spawnWater(object->position, direction);
        }
    }
    World::update(delta);
}

void WaterWorld::spawnWater(const sf::Vector2i& position, zf::Direction direction)
{
    auto mod = zf::getModifier(direction);
    auto targetPosition = position + mod;
    if (inRange(targetPosition))
    {
        auto object = getObject(targetPosition);
        if (object == nullptr)
        {
            WaterObject* object = new WaterObject(game, *this);
            if(!addObject(object, targetPosition))
            {
                delete object; // shouldn't happen but take care in case.
            }
        }
        else if (object->type == WorldObject::ObjectType::WaterObject)
        {
            auto water = static_cast<WaterObject*>(object);
            water->floodMeter += 1;
        }
    }
}
