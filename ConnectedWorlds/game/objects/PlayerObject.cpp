#include "PlayerObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
int PlayerObject::FoodIncreaseAmount = 25;
PlayerObject::PlayerObject(Game& game, World& world)
    : WorldObject(game, world, WorldObject::ObjectType::PlayerObject), food(100), work(0)
    , foodDepleteRate(10), workCostRate(10)
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
    if (foodDepleteCounter >= foodDepleteRate)
    {
        foodDepleteCounter -= foodDepleteRate;
        food--;
    }
}

void PlayerObject::doWork(int amount)
{
    work += amount;
    while (work > workCostRate)
    {
        work -= workCostRate;
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
    food += FoodIncreaseAmount;
    food = food >= 100 ? 100 : food;
}
