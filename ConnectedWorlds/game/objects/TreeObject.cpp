#include "TreeObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"

TreeObject::TreeObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::TreeObject), currentStage(0)
{
    background = game.getSpecialCharSprite(zf::Fill);
    background.setColor(sf::Color(50, 120, 50));
    sprite[0] = game.getCharSprite('.');
    sprite[1] = game.getCharSprite(',');
    sprite[2] = game.getCharSprite('i');
    sprite[3] = game.getCharSprite('t');
    sprite[4] = game.getCharSprite('T');
    for (int i = 0; i < STAGES; i++)
    {
        sprite[i].setColor(sf::Color(0, 255, 0, 255));
    }
}

TreeObject::~TreeObject()
{
}

void TreeObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite[currentStage]);
    if (grabbed)
    {
        window->putSprite_xyb(position.x, position.y, background);
    }
}

bool TreeObject::canBeGrabbed() const
{
    return true;
}
