#include "World.hpp"
#include "WorldObject.hpp"
#include "PlayerObject.hpp"
#include "Game.hpp"
#include <iostream>
World::World(Game& game, int worldId)
    : selected(false), game(game), player(nullptr)
{
    for (int x = 0; x < Game::WorldSize.x; x++)
    {
        std::vector<WorldObject*> columns;
        for(int y = 0; y < Game::WorldSize.y; y++)
        {
            columns.push_back(nullptr);
        } 
        objects.push_back(columns);
    }
    player = new PlayerObject(game, worldId);
    addObject(player, sf::Vector2i(5, 5));
}

World::~World()
{
}

void World::draw(zf::TermWindow* window, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    if (selected)
    {
        window->clear(sf::Color(150, 150, 150, 255));
    }
    else 
    {
        window->clear(sf::Color(80, 80, 80, 255));
    }
    for (auto object : objectsAsList)
    {
        object->draw(window, delta);
    }
}

void World::setSelected(bool selected)
{
    this->selected = selected;
}

void World::processAction(Action action)
{
    if (action == Action::Up)
    {
        move(zf::Direction::North);
    }
    else if (action == Action::Down)
    {
        move(zf::Direction::South);
    }
    else if (action == Action::Left)
    {
        move(zf::Direction::West);
    }
    else if (action == Action::Right)
    {
        move(zf::Direction::East);
    }
}

bool World::inRange(const sf::Vector2i& position) const
{
    return position.x >= 0 && position.y >= 0 && position.x < Game::WorldSize.x && position.y < Game::WorldSize.y;
}

bool World::canAddObject(WorldObject* object, const sf::Vector2i& position) const
{
    if (!inRange(position))
    {
        return false;
    }
    return getObject(position) == nullptr;
}

bool World::addObject(WorldObject* object, const sf::Vector2i& position)
{
    if (!canAddObject(object, position) || !object)
    {
        return false;
    }
    objects[position.x][position.y] = object;
    objectsAsList.push_back(object);
    object->position = position;
    return true;
}

WorldObject* World::getObject(const sf::Vector2i& position) const
{
    return inRange(position) ? objects[position.x][position.y] : nullptr;
}

void World::move(zf::Direction direction)
{
    if (player)
    {
        auto mod = zf::getModifier(direction);
        auto targetPosition = player->position + mod;
        if (inRange(targetPosition))
        {
            player->position = targetPosition;
        }
    }
}
