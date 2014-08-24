#include "ForestWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_conversion.hpp"
#include "../f_rng.hpp"
ForestWorld::ForestWorld(Game& game)
    : World(game, World::Type::Forest)
{
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(7, 7));

    spawnObject(new TreeObject(game, *this));
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
        window->clear(sf::Color(50, 70, 50));
    }
    else
    {
        window->clear(sf::Color(0, 70, 0));
    }
    World::draw(window, objectsWindow, infoWindow, overlayWindow, delta);
    infoWindow->putString_xy(0, 0, "(2)");
    infoWindow->putString("F"+zf::intToString(player->food));
}

void ForestWorld::update(const sf::Time& delta)
{
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::TreeObject)
        {
            auto object = static_cast<TreeObject*>(block);
            if (object->hasFood())
            {
                block->markedForRemoval = true;
                block->isSpawnElsewhere = true;
                spawnObject(new TreeObject(game, *this));
            }
        }
    }
    World::update(delta);
}
