#include "FoodObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
FoodObject::FoodObject(Game& game, World& world)
    : WorldObject(game, world, WorldObject::ObjectType::FoodObject)
{
    sprite = zf::setCopyColor(game.getCharSprite('%'), sf::Color(0, 255, 0));
    grabbedBackground = zf::setCopyColor(game.getSpecialCharSprite(zf::Fill), sf::Color(50, 100, 50, 255));
}

FoodObject::~FoodObject()
{
}

void FoodObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    if (grabbed)
    {
        window->putSprite_xyfb(position.x, position.y, sprite, grabbedBackground);
    }
    else
    {
        window->putSprite_xyf(position.x, position.y, sprite);
    }
}
