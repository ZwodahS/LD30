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
#include "VolcanoWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../Game.hpp"
#include "../f_rng.hpp"
#include "../../zf/zf_conversion.hpp"
VolcanoWorld::VolcanoWorld(Game& game)
    : World(game, World::Type::Volcano)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(6, 7));
    volcano = new VolcanoObject(game, *this);
    addObject(volcano, sf::Vector2i(7, 7)); 
    erupt(7);
}

VolcanoWorld::~VolcanoWorld()
{
}

void VolcanoWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(70, 50, 50));
    }
    else
    {
        window->clear(sf::Color(70, 0, 0));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(4)");
    infoWindow->putString("F"+zf::intToString(player->food));
    infoWindow->putString(" V"+zf::intToString(volcano->time));
}

void VolcanoWorld::update(const sf::Time& delta)
{
    World::update(delta);
    seconds += delta.asSeconds();
    if (seconds > 1)
    {
        seconds -= 1;
        volcano->time -= 1;
    }
    if (volcano->time <= 0)
    {
        volcano->time = game.balance.Volcano_EruptFrequency;
        if (!erupt(rng::randomInt(game.balance.Volcano_EruptMin, game.balance.Volcano_EruptMax)))
        {
            isAlive = false;
        }
    }
}

bool VolcanoWorld::erupt(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        AshObject* object = new AshObject(game, *this, zf::SurroundingDirection[rng::randomInt(0, 7)]);
        if (!spawnObject(object))
        {
            delete object;
            return false;
        }
    }
    return true;
}
