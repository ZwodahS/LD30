#ifndef _GAME_WORLDS_WORLD_HPP_
#define _GAME_WORLDS_WORLD_HPP_
#include "../../zf/zf_term.hpp"
#include "../../zf/zf_direction.hpp"
#include "../KeyMap.hpp"
#include <vector>
#include <list>
/**
 * World defines one of the world.
 */
class WorldObject;
class PlayerObject;
class Game;
class World
{
public:
    enum class Type
    {
        Volcano,
        Forest,
        Sand,
        Water,
    };
    World(Game& game, Type worldType);
    virtual ~World();

    const Type worldType;
    const int worldId;
    virtual void draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta);
    virtual void update(const sf::Time& delta);

    virtual void setSelected(bool selected);

    virtual void processAction(Action action);
    
    std::vector<std::vector<WorldObject*> > objects;
    virtual bool inRange(const sf::Vector2i& position) const;
    virtual bool canAddObject(WorldObject* object, const sf::Vector2i& position) const;
    virtual bool addObject(WorldObject* object, const sf::Vector2i& position);
    virtual WorldObject* getObject(const sf::Vector2i& position) const;
    virtual std::vector<sf::Vector2i> getAvailablePositions() const;
    virtual std::vector<WorldObject*> getOutputBlocks();
    /**
     * if cannot spawn the return false;
     */
    virtual bool spawnObject(WorldObject* object);
    virtual std::vector<WorldObject*> getAdjacentBlocks(const sf::Vector2i& position) const;
    int countEmptySpot(const sf::Vector2i& position) const;

    bool isAlive;
protected:
    bool selected;
    Game& game;
    PlayerObject* player;

    std::list<WorldObject*> objectsAsList;
    std::vector<WorldObject*> outputBlocks;

    void removeFromGrid(WorldObject* object);
    void removeFromList(WorldObject* object);
    void move(zf::Direction direction);
    void moveObject(WorldObject& object, const sf::Vector2i& position);
};
#endif
