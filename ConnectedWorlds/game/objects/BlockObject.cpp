#include "BlockObject.hpp"
#include "../Game.hpp"
#include "../World.hpp"
#include "../../zf/zf_term.hpp"
#include <iostream>
const sf::Color BlockObject::colors[4] = { 
    sf::Color(255, 120, 120, 255), 
    sf::Color(120, 255, 120, 255), 
    sf::Color(120, 120, 255, 255), 
    sf::Color(255, 255, 120, 255) 
};
const sf::Color BlockObject::grabbedColors[4] = { 
    sf::Color(255, 180, 180, 255), 
    sf::Color(180, 255, 180, 255), 
    sf::Color(180, 180, 255, 255), 
    sf::Color(255, 255, 180, 255) 
};
BlockObject::BlockObject(Game& game, World& world, int colorType, zf::Direction orientation, int level)
    : WorldObject(game, world, ObjectType::BlockObject), orientation(orientation), colorType(colorType), level(level)
{
    auto outDirection = getOutputDirections();
    if (outDirection.size() == 2)
    {
        int bitValue = zf::toBit(outDirection[0]) | zf::toBit(outDirection[1]);
        sprite = game.getSpecialCharSprite(zf::Cross[bitValue]);
    }
    sprite.setColor(sf::Color::White);
    normalBackground = game.getSpecialCharSprite(zf::Fill);
    normalBackground.setColor(colors[colorType]);
    grabbedBackground = normalBackground;
    grabbedBackground.setColor(grabbedColors[colorType]);
}

BlockObject::~BlockObject()
{
}

void BlockObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyb(position.x, position.y, grabbed ? grabbedBackground : normalBackground);
    window->putSprite_xyf(position.x, position.y, sprite);
}

std::vector<zf::Direction> BlockObject::getOutputDirections() const
{
    return getOutputDirections(orientation);
}

std::vector<zf::Direction> BlockObject::getOutputDirections(zf::Direction orientation)
{
    std::vector<zf::Direction> output;
    if (orientation == zf::Direction::North || orientation == zf::Direction::South 
            || orientation == zf::Direction::East || orientation == zf::Direction::West)
    {
        output.push_back(orientation);
        output.push_back(zf::oppositeOf(orientation));
    }
    else
    {
        int bit = zf::toBit(orientation);
        for (auto direction : zf::AdjacentDirection)
        {
            if (bit & zf::toBit(direction))
            {
                output.push_back(direction);
            }
        }
    }
    return output;
}

std::vector<BlockObject*> BlockObject::getConnectedBlocks() const
{
    std::vector<BlockObject*> connected;
    if (!grabbed && world)
    {
        auto outDirection = getOutputDirections();
        for (auto direction : outDirection)
        {
            auto mod = zf::getModifier(direction);
            auto object = world->getObject(position + mod);
            if (object && object->type == WorldObject::ObjectType::BlockObject)
            {
                auto blockObject = static_cast<BlockObject*>(object);
                if (blockObject->canConnectFrom(zf::oppositeOf(direction)))
                {
                    connected.push_back(blockObject);
                }
            }
        }
    }
    return connected;
}

bool BlockObject::canConnectFrom(zf::Direction direction) const
{
    if (grabbed)
    {
        return false;
    }
    auto outDirections = getOutputDirections();
    return std::find(outDirections.begin(), outDirections.end(), direction) != outDirections.end();
}

bool BlockObject::canBeGrabbed() const
{
    return true;
}
