#include "WaterWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
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
    World::update(delta);
}
