#include "WorldObject.hpp"
#include "../Game.hpp"
#include "../World.hpp"
WorldObject::WorldObject(Game& game, World& world, ObjectType type)
    : type(type), game(game), world(&world), markedForRemoval(false), isSpawnElsewhere(false)
{
}

WorldObject::~WorldObject()
{
}

bool WorldObject::canPush(zf::Direction direction)
{
    auto mod = zf::getModifier(direction);
    auto targetPosition = position + mod;
    if (world && world->inRange(targetPosition))
    {
        auto object = world->getObject(targetPosition);
        return object ? false : true;
        // return object ? object->canPush(direction) : true; // cascading push
    }
    return false;
}

void WorldObject::reset()
{
    markedForRemoval = false;
    isSpawnElsewhere = false;
}
