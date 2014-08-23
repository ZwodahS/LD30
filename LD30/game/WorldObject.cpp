#include "WorldObject.hpp"
#include "Game.hpp"
WorldObject::WorldObject(Game& game, ObjectType type)
    : type(type), game(game)
{
}

WorldObject::~WorldObject()
{
}

