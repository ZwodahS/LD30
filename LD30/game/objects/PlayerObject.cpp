#include "PlayerObject.hpp"
#include "../Game.hpp"
#include "../World.hpp"
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
