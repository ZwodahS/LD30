#include "SandWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
SandWorld::SandWorld(Game& game)
    : World(game, World::Type::Sand)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));
    for (int i = 0; i < 10; i++)
    {
        spawnObject(new SandObject(game, *this));
    }
}

SandWorld::~SandWorld()
{
}

void SandWorld::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    infoWindow->empty();
    objectsWindow->empty();
    if (!selected)
    {
        window->clear(sf::Color(50, 50, 32));
    }
    else
    {
        window->clear(sf::Color(100, 100, 75));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(3)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void SandWorld::update(const sf::Time& delta)
{
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::SandObject)
        {
            SandObject* object = static_cast<SandObject*>(block);
            if (object->count == 4)
            {
                block->markedForRemoval = true;
                block->isSpawnElsewhere = true;
                spawnObject(new SandObject(game, *this));
            }
        }
    }
    World::update(delta);
}
