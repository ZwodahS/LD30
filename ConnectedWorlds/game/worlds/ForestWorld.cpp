#include "ForestWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
ForestWorld::ForestWorld(Game& game)
    : World(game, World::Type::Forest)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));
}

ForestWorld::~ForestWorld()
{
}

void ForestWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(32, 50, 32));
    }
    else
    {
        window->clear(sf::Color(75, 100, 75));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(2)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void ForestWorld::update(const sf::Time& delta)
{
    World::update(delta);
}
