#include "WaterObject.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include "../../zf/zf_sprite.hpp"
#include "../f_rng.hpp"
#include <iostream>
WaterObject::WaterObject(Game& game, World& world)
    : WorldObject(game, world, ObjectType::WaterObject), flood(true), floodMeter(0)
{
    sprite = zf::setCopyColor(game.getSpecialCharSprite(game.Special_Water), sf::Color(0, 0, 255, 255));
    background = zf::setCopyColor(game.getSpecialCharSprite(zf::Fill), sf::Color(100, 100, 255, 0));
}

WaterObject::~WaterObject()
{
}

void WaterObject::draw(zf::TermWindow* window, const sf::Time& delta)
{
    if (flood) 
    {
        background.setColor(sf::Color(100, 100, 255, floodMeter * 25));
        window->putSprite_xyfb(position.x, position.y, sprite, background);
    }
    else
    {
        window->putSprite_xyf(position.x, position.y, sprite);
    }
}

void WaterObject::update(const sf::Time& delta)
{
    timePassed += delta.asSeconds();
    WorldObject::update(delta);
    if (timePassed >= 1)
    {
        timePassed -= 1;
        if (flood && floodMeter < 10 && rng::randomInt(0, 100) < game.balance.Water_FloodProbability)
        {
            floodMeter++;
        }
    }
}

bool WaterObject::isPushable() const
{
    return false;
}
