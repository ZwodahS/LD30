#include "PlayerObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
PlayerObject::PlayerObject(Game& game, World& world)
    : WorldObject(game, world, WorldObject::ObjectType::PlayerObject)
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
