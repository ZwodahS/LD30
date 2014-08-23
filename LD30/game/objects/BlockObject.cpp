#include "BlockObject.hpp"
#include "../Game.hpp"
#include "../World.hpp"
#include "../../zf/zf_term.hpp"
#include <iostream>
const sf::Color BlockObject::colors[4] = { sf::Color(200, 120, 120, 255), sf::Color(120, 200, 120, 255), sf::Color(120, 120, 200, 255), sf::Color(200, 200, 120, 255) };
BlockObject::BlockObject(Game& game, World& world, int colorType, zf::Direction orientation, int level)
    : EnvironmentObject(game, world, EnvObjectType::BlockType), orientation(orientation), colorType(colorType), level(level)
{
    auto outDirection = getOutputDirection();
    if (outDirection.size() == 2)
    {
        int bitValue = zf::toBit(outDirection[0]) | zf::toBit(outDirection[1]);
        sprite = game.getSpecialCharSprite(zf::Cross[bitValue]);
    }
    sprite.setColor(sf::Color::White);
    background = game.getSpecialCharSprite(zf::Fill);
    background.setColor(colors[colorType]);
}

BlockObject::~BlockObject()
{
}

void BlockObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    window->putSprite_xyb(position.x, position.y, background);
    window->putSprite_xyf(position.x, position.y, sprite);
}

std::vector<zf::Direction> BlockObject::getOutputDirection() const
{
    return getOutputDirection(orientation);
}

std::vector<zf::Direction> BlockObject::getOutputDirection(zf::Direction orientation)
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
