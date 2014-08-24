#include "VolcanoObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
VolcanoObject::VolcanoObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::VolcanoObject), time(30)
{
    background = game.getSpecialCharSprite(zf::Fill);
    background.setColor(sf::Color(200, 50, 50));
    sprite = game.getSpecialCharSprite(game.Special_Volcano);
}

VolcanoObject::~VolcanoObject()
{
}

void VolcanoObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyfb(position.x, position.y, sprite, background);
}

bool VolcanoObject::isPushable() const
{
    return false;
}

bool VolcanoObject::canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const
{
    return false;
}

bool VolcanoObject::canBeGrabbed() const
{
    return false;
}
