#include "VolcanoWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../f_rng.hpp"
#include "../../zf/zf_conversion.hpp"
VolcanoWorld::VolcanoWorld(Game& game)
    : World(game, World::Type::Volcano)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(6, 7));
    volcano = new VolcanoObject(game, *this);
    addObject(volcano, sf::Vector2i(7, 7)); 
    erupt(7);
}

VolcanoWorld::~VolcanoWorld()
{
}

void VolcanoWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(50, 32, 32));
    }
    else
    {
        window->clear(sf::Color(100, 75, 75));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(1)");
    infoWindow->putString("F"+zf::intToString(player->food));
    infoWindow->putString(" V"+zf::intToString(volcano->time));
}

void VolcanoWorld::update(const sf::Time& delta)
{
    World::update(delta);
    seconds += delta.asSeconds();
    if (seconds > 1)
    {
        seconds -= 1;
        volcano->time -= 1;
    }
    if (volcano->time <= 0)
    {
        volcano->time = 20;
        if (!erupt(rng::randomInt(5, 10)))
        {
            // GAMEOVER
        }
    }
}

bool VolcanoWorld::erupt(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        AshObject* object = new AshObject(game, *this, zf::SurroundingDirection[rng::randomInt(0, 7)]);
        if (!spawnObject(object))
        {
            delete object;
            return false;
        }
    }
    return true;
}
