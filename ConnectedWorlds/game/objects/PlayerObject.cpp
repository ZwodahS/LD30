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
#include "PlayerObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
int PlayerObject::FoodIncreaseAmount = 25;
PlayerObject::PlayerObject(Game& game, World& world)
    : WorldObject(game, world, WorldObject::ObjectType::PlayerObject), food(game.balance.Player_InitialFood), work(0)
{
    sprite = game.getPlayerSprite(world.worldId);
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite);
}

void PlayerObject::update(const sf::Time& delta)
{
    foodDepleteCounter += delta.asSeconds();
    if (foodDepleteCounter >= game.balance.Player_FoodDepleteRate)
    {
        foodDepleteCounter -= game.balance.Player_FoodDepleteRate;
        food--;
    }
}

void PlayerObject::doWork(int amount)
{
    work += amount;
    while (work > game.balance.Player_WorkDepleteRate)
    {
        work -= game.balance.Player_WorkDepleteRate;
        food--;
    }
}

bool PlayerObject::canPush(zf::Direction direction) const
{
    return false;
}

bool PlayerObject::isGrabbing() const
{
    return grabbedObjects.size() > 0;
}

void PlayerObject::toggleGrab()
{
    if (!world)
    {
        return ;
    }
    if (isGrabbing())
    {
        for (auto object : grabbedObjects)
        {
            object->drop();
        }
        grabbedObjects.clear();
    }
    else
    {
        auto adjacents = world->getAdjacentBlocks(position);
        for (auto object : adjacents)
        {
            if (object->grab())
            {
                grabbedObjects.push_back(object);
            }
        }
    }
}

const std::vector<WorldObject*>& PlayerObject::getGrabbedObjects() const
{
    return grabbedObjects;
}

void PlayerObject::eat()
{
    food += game.balance.Player_FoodIncreaseAmount;
    food = food >= 100 ? 100 : food;
}
