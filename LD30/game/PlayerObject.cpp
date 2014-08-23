#include "PlayerObject.hpp"
#include "Game.hpp"
#include <iostream>
PlayerObject::PlayerObject(Game& game, int worldId)
    : WorldObject(game, WorldObject::ObjectType::PlayerObject)
{
    sprite = game.getPlayerSprite(worldId);
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite);
}
