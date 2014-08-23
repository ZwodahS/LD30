#include "EnvironmentObject.hpp"
EnvironmentObject::EnvironmentObject(Game& game, World& world, EnvObjectType envType)
    : WorldObject(game, world, ObjectType::EnvironmentObject), envType(envType)
{
}

EnvironmentObject::~EnvironmentObject()
{
}
