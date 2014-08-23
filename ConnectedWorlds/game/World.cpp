#include "World.hpp"
#include "objects/WorldObject.hpp"
#include "objects/PlayerObject.hpp"
#include "objects/BlockObject.hpp"
#include "Game.hpp"
#include "f_rng.hpp"
#include <iostream>
World::World(Game& game, int worldId)
    : selected(false), game(game), player(nullptr), worldId(worldId)
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
    player = new PlayerObject(game, *this);
    addObject(player, sf::Vector2i(5, 5));
    
    std::vector<BlockObject*> blocks;
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::North, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::NorthEast, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::NorthWest, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::South, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::SouthEast, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::SouthWest, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::East, 1));
    blocks.push_back(new BlockObject(game, *this, worldId, zf::Direction::West, 1));

    auto availablePositions = getAvailablePositions();
    for (auto block : blocks)
    {
        auto position = rng::randomItem(availablePositions, sf::Vector2i(0, 0), true);
        addObject(block, position);
    }
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

void World::update(const sf::Time& delta)
{
    for (auto block : blockObjects)
    {
        auto connected = block->getConnectedBlocks();
        if (connected.size() >= 2)
        {
            block->markedForRemoval = true;
            block->isSpawnElsewhere = true;
            for (auto connectedBlock : connected)
            {
                connectedBlock->markedForRemoval = true;
            }
        }
    }
    for (auto it = objectsAsList.begin(); it != objectsAsList.end();)
    {
        if ((**it).markedForRemoval)
        {
            auto object = *it;
            it = objectsAsList.erase(it);
            removeFromGrid(object);
            if (object->type == WorldObject::ObjectType::BlockObject)
            {
                removeFromBlockList(static_cast<BlockObject*>(object));
            }
            if (object->isSpawnElsewhere)
            {
                object->world = nullptr;
                outputBlocks.push_back(object);
            }
            else
            {
                delete object;
            }
        }
        else
        {
            it++;
        }
    }
}

std::vector<WorldObject*> World::getOutputBlocks()
{
    std::vector<WorldObject*> out = outputBlocks;
    outputBlocks.clear();
    return out;
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

std::vector<sf::Vector2i> World::getAvailablePositions() const
{
    std::vector<sf::Vector2i> positions;
    for (int x = 0; x < game.WorldSize.x; x++)
    {
        for (int y = 0; y < game.WorldSize.y; y++)
        {
            if (objects[x][y] == nullptr)
            {
                positions.push_back(sf::Vector2i(x, y));
            }
        }
    }
    return positions;
}

bool World::inRange(const sf::Vector2i& position) const
{
    return position.x >= 0 && position.y >= 0 && position.x < Game::WorldSize.x && position.y < Game::WorldSize.y;
}

bool World::spawnObject(WorldObject* object)
{
    auto availablePositions = getAvailablePositions();
    object->world = this;
    object->reset();
    if (availablePositions.size() == 0)
    {
        return false;
    }
    auto position = rng::randomItem(availablePositions, sf::Vector2i(0, 0), true);
    addObject(object, position);
    return true;
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
    if (object->type == WorldObject::ObjectType::BlockObject)
    {
        blockObjects.push_back(static_cast<BlockObject*>(object));
    }
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
            auto object = getObject(targetPosition);
            if (!object)
            {
                moveObject(*player, targetPosition);
            }
            else if (object->canPush(direction))
            {
                moveObject(*player, targetPosition);
                moveObject(*object, targetPosition + mod);
            }
        }
    }
}

void World::moveObject(WorldObject& object, const sf::Vector2i& position)
{
    objects[object.position.x][object.position.y] = nullptr;
    object.position = position;
    objects[object.position.x][object.position.y] = &object;
}

std::vector<WorldObject*> World::getAdjacentBlocks(const sf::Vector2i& position) const
{
    std::vector<WorldObject*> objects;
    for (auto direction : zf::AdjacentDirection)
    {
        auto mod = zf::getModifier(direction);
        auto targetPosition = mod + position;
        auto object = getObject(targetPosition);
        if (object)
        {
            objects.push_back(object);
        }
    }
    return objects;
}

void World::removeFromGrid(WorldObject* object)
{
    objects[object->position.x][object->position.y] = nullptr;
}

void World::removeFromBlockList(BlockObject* block)
{
    auto found = std::find(blockObjects.begin(), blockObjects.end(), block);
    if (found != blockObjects.end())
    {
        blockObjects.erase(found);
    }
}