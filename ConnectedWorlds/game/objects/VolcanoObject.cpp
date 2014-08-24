#include "VolcanoObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include <iostream>
VolcanoObject::VolcanoObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::VolcanoObject)
{
    sprite = game.getCharSprite('^');
    sprite.setColor(sf::Color(255, 0, 0, 255));

}

VolcanoObject::~VolcanoObject()
{
}

void VolcanoObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyf(position.x, position.y, sprite);
}

bool VolcanoObject::canPush(zf::Direction) const
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
