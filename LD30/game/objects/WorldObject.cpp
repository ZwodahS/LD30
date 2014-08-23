#include "WorldObject.hpp"
#include "../Game.hpp"
WorldObject::WorldObject(Game& game, World& world, ObjectType type)
    : type(type), game(game), world(world)
{
}

WorldObject::~WorldObject()
{
}

