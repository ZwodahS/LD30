#include "StoneObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include "../../zf/zf_sprite.hpp"
StoneObject::StoneObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::StoneObject)
{
    sprite = zf::setCopyColor(game.getCharSprite('O'), sf::Color(150, 150, 150));
    background = zf::setCopyColor(game.getSpecialCharSprite(zf::Fill), sf::Color(50, 50, 50));
}

StoneObject::~StoneObject()
{
}

void StoneObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite);
    if (grabbed)
    {
        window->putSprite_xyb(position.x, position.y, background);
    }
}

bool StoneObject::canBeGrabbed() const
{
    return true;
}
