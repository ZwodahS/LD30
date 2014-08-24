#include "World.hpp"
#include "../objects/g_objects.hpp"
#include "../Game.hpp"
#include "../f_rng.hpp"
#include <iostream>
World::World(Game& game, World::Type worldType)
    : selected(false), game(game), player(nullptr), worldType(worldType)
    , worldId(worldType == Type::Volcano ? 0 : worldType == Type::Forest ? 1 : worldType == Type::Sand ? 2 : 3), isAlive(true)
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
}

World::~World()
{
    for (auto object : objectsAsList)
    {
        delete object;
    }
}

void World::draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta)
{
    for (auto object : objectsAsList)
    {
        object->draw(objectsWindow, delta);
    }
}

void World::update(const sf::Time& delta)
{
    for (auto block : objectsAsList)
    {
        if (block->type == WorldObject::ObjectType::AshObject)
        {
            AshObject* object = static_cast<AshObject*>(block);
            auto connected = object->getConnectedBlocks();
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
    }
    for (auto it = objectsAsList.begin(); it != objectsAsList.end();)
    {
        if ((**it).markedForRemoval)
        {
            auto object = *it;
            it = objectsAsList.erase(it);
            removeFromGrid(object);
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
            (**it).update(delta);
            it++;
        }
    }
    if (player && isAlive)
    {
        if (player->food <= 0 || (countEmptySpot(player->position) == 0 && !player->isGrabbing()))
        {
            isAlive = false;
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
    else if (action == Action::Select)
    {
        if (player)
        {
            player->toggleGrab();
        }
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
        if (player->isGrabbing())
        {
            auto mod = zf::getModifier(direction);
            auto playerTargetPosition = player->position + mod;
            bool canMove = true;
            if (inRange(playerTargetPosition))
            {
                auto grabbed = player->getGrabbedObjects();
                auto destinationObject = getObject(playerTargetPosition);
                if (!destinationObject || std::find(grabbed.begin(), grabbed.end(), destinationObject) != grabbed.end())
                {
                    for (auto object : grabbed)
                    {
                        if (!object->canGrabbed(direction, *player, grabbed))
                        {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove)
                    {
                        moveObject(*player, player->position + mod);
                        for (auto object : grabbed)
                        {
                            moveObject (*object, object->position + mod);
                        }
                        player->doWork(1 + grabbed.size());
                    }
                }
            }

        }
        else
        {
            auto mod = zf::getModifier(direction);
            auto targetPosition = player->position + mod;
            if (inRange(targetPosition))
            {
                auto object = getObject(targetPosition);
                auto objectTargetPosition = targetPosition + mod;
                if (!object)
                {
                    moveObject(*player, targetPosition);
                    player->doWork(1);
                }
                else if (object->type == WorldObject::ObjectType::FoodObject)
                {
                    player->eat();
                    removeFromGrid(object);
                    removeFromList(object);
                    delete object;
                    moveObject(*player, targetPosition);
                }
                else if (inRange(objectTargetPosition))
                {
                    auto objectObstacle = getObject(objectTargetPosition);
                    if (!object->isPushable())
                    {
                    }
                    else if (!objectObstacle)
                    {
                        moveObject(*player, targetPosition);
                        moveObject(*object, targetPosition + mod);
                        player->doWork(2);
                    }
                    /// cant push, see if we can combine
                    else if (object->type == WorldObject::ObjectType::SandObject && objectObstacle->type == WorldObject::ObjectType::SandObject)
                    {
                        // merge the sand object
                        auto sandSource = static_cast<SandObject*>(object);
                        auto sandTarget = static_cast<SandObject*>(objectObstacle);
                        if (sandSource->count + sandTarget->count <= 4)
                        {
                            // can only merge if their total is < 4
                            sandTarget->count += sandSource->count;
                            // respawn sandSource
                            sandSource->count = 1;
                            removeFromGrid(sandSource);
                            removeFromList(sandSource);
                            moveObject(*player, targetPosition);
                            spawnObject(sandSource);
                        }
                    }
                    else if (object->type == WorldObject::ObjectType::SandObject && objectObstacle->type == WorldObject::ObjectType::WaterObject)
                    {
                        auto sandSource = static_cast<SandObject*>(object);
                        auto waterTarget = static_cast<WaterObject*>(objectObstacle);
                        if (waterTarget->flood)
                        {
                            removeFromGrid(waterTarget);
                            removeFromList(waterTarget);
                            waterTarget->flood = false;
                            waterTarget->floodMeter = 0;
                            outputBlocks.push_back(waterTarget);
                            sandSource->count-=1;
                            if (sandSource->count <= 0)
                            {
                                removeFromGrid(sandSource);
                                removeFromList(sandSource);
                                delete sandSource;
                            }
                            else
                            {
                                moveObject(*sandSource, objectTargetPosition);
                            }
                            moveObject(*player, targetPosition);
                        }
                    }
                    else if (object->type == WorldObject::ObjectType::TreeObject && objectObstacle->type == WorldObject::ObjectType::WaterObject)
                    {
                        auto treeSource = static_cast<TreeObject*>(object);
                        auto waterTarget = static_cast<WaterObject*>(objectObstacle);
                        if (treeSource->grow())
                        {
                            removeFromGrid(waterTarget);
                            removeFromList(waterTarget);
                            delete waterTarget;
                            moveObject(*treeSource, objectTargetPosition);
                            moveObject(*player, targetPosition);
                        }
                    }
                }
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

void World::removeFromList(WorldObject* object)
{
    auto result = std::find(objectsAsList.begin(), objectsAsList.end(), object);
    if (result != objectsAsList.end())
    {
        objectsAsList.erase(result);
    }
}

int World::countEmptySpot(const sf::Vector2i& position) const
{
    int count = 0;
    for (auto direction : zf::AdjacentDirection)
    {
        auto mod = zf::getModifier(direction);
        auto target = position + mod;
        if (inRange(target) && getObject(target) == nullptr)
        {
            count++;
        }
    }
    return count;
}
