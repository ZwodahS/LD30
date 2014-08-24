#include "SandObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include "../../zf/zf_sprite.hpp"
SandObject::SandObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::SandObject), count(1)
{
    sprite[0] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand1), sf::Color(255, 255, 0, 255));
    sprite[1] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand2), sf::Color(255, 255, 0, 255));
    sprite[2] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand3), sf::Color(255, 255, 0, 255));
    sprite[3] = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Sand4), sf::Color(255, 255, 0, 255));
}

SandObject::~SandObject()
{
}

void SandObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite[count - 1]);
}
