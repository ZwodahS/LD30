#ifndef _GAME_WORLD_HPP_
#define _GAME_WORLD_HPP_
#include "../zf/zf_term.hpp"
#include "../zf/zf_direction.hpp"
#include "KeyMap.hpp"
#include <vector>
#include <list>
/**
 * World defines one of the world.
 */
class WorldObject;
class PlayerObject;
class BlockObject;
class Game;
class World
{
public:
    World(Game& game, int worldId);
    ~World();

    const int worldId;
    void draw(zf::TermWindow* window, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta);
    void update(const sf::Time& delta);

    void setSelected(bool selected);

    void processAction(Action action);
    
    std::vector<std::vector<WorldObject*> > objects;
    bool inRange(const sf::Vector2i& position) const;
    bool canAddObject(WorldObject* object, const sf::Vector2i& position) const;
    bool addObject(WorldObject* object, const sf::Vector2i& position);
    WorldObject* removeObject(WorldObject* object);
    WorldObject* getObject(const sf::Vector2i& position) const;
    std::vector<sf::Vector2i> getAvailablePositions() const;
    std::vector<WorldObject*> getOutputBlocks();
    /**
     * if cannot spawn the return false;
     */
    bool spawnObject(WorldObject* object);
    std::vector<WorldObject*> getAdjacentBlocks(const sf::Vector2i& position) const;
private:
    bool selected;
    Game& game;

    std::list<WorldObject*> objectsAsList;
    std::vector<WorldObject*> outputBlocks;

    /**
     * block objects stored separately, since we need to calculate.
     */
    std::vector<BlockObject*> blockObjects;
    void removeFromGrid(WorldObject* object);
    void removeFromBlockList(BlockObject* block);
    PlayerObject* player;

    void move(zf::Direction direction);

    void moveObject(WorldObject& object, const sf::Vector2i& position);
};
#endif
