#include "WaterWorld.hpp"
#include "../Game.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
WaterWorld::WaterWorld(Game& game)
    : World(game, World::Type::Water)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
        for (int y = game.WorldSize.y - 3; y < game.WorldSize.y; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
    }
    for (int x = game.WorldSize.x - 3; x < game.WorldSize.x; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
        for (int y = game.WorldSize.y - 3; y < game.WorldSize.y; y++)
        {
            addObject(new WaterObject(game, *this), sf::Vector2i(x, y));
        }
    }
}

WaterWorld::~WaterWorld()
{
}

void WaterWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(32, 32, 50));
    }
    else
    {
        window->clear(sf::Color(75, 75, 100));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(4)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void WaterWorld::update(const sf::Time& delta)
{
    std::vector<WaterObject*> flooded;
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::WaterObject)
        {
            WaterObject* object = static_cast<WaterObject*>(block);
            if (object->floodMeter >= 10)
            {
                object->floodMeter = 0;
                flooded.push_back(object);
            }
        }
    }
    for (auto object : flooded)
    {
        for (auto direction : zf::AdjacentDirection)
        {
            spawnWater(object->position, direction);
        }
    }
    World::update(delta);
}

void WaterWorld::spawnWater(const sf::Vector2i& position, zf::Direction direction)
{
    auto mod = zf::getModifier(direction);
    auto targetPosition = position + mod;
    if (inRange(targetPosition))
    {
        auto object = getObject(targetPosition);
        if (object == nullptr)
        {
            WaterObject* object = new WaterObject(game, *this);
            if(!addObject(object, targetPosition))
            {
                delete object; // shouldn't happen but take care in case.
            }
        }
        else if (object->type == WorldObject::ObjectType::WaterObject)
        {
            auto water = static_cast<WaterObject*>(object);
            water->floodMeter += 1;
        }
    }
}
