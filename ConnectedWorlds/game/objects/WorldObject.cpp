#include "WorldObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
WorldObject::WorldObject(Game& game, World& world, ObjectType type)
    : type(type), game(game), world(&world), markedForRemoval(false), isSpawnElsewhere(false), grabbed(false)
{
}

WorldObject::~WorldObject()
{
}

void WorldObject::update(const sf::Time& delta)
{
}

bool WorldObject::isPushable() const
{
    return true;
}

bool WorldObject::canBeGrabbed() const
{
    return false;
}

void WorldObject::reset()
{
    markedForRemoval = false;
    isSpawnElsewhere = false;
}

bool WorldObject::grab()
{
    if (!canBeGrabbed())
    {
        return false;
    }
    grabbed = true;
    return grabbed;
}

void WorldObject::drop()
{
    grabbed = false;
}
bool WorldObject::canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const
{
    auto mod = zf::getModifier(direction);
    auto targetPosition = position + mod;
    if (world && world->inRange(targetPosition))
    {
        auto object = world->getObject(targetPosition);
        return !object ? true : object == &grabber ? true : false;
    }
    return false;
}
