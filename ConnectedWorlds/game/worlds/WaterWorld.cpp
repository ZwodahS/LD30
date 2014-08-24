#include "WaterWorld.hpp"
#include "../objects/g_objects.hpp"
WaterWorld::WaterWorld(Game& game)
    : World(game, World::Type::Water)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));
}

WaterWorld::~WaterWorld()
{
}

void WaterWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
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
}

void WaterWorld::update(const sf::Time& delta)
{
    World::update(delta);
}
