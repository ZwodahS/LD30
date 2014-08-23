#ifndef _GAME_WORLD_HPP_
#define _GAME_WORLD_HPP_
#include "../zf/zf_term.hpp"
#include "KeyMap.hpp"
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
    World(Game& game, int worldId);
    ~World();

    void draw(zf::TermWindow* window, const sf::Time& delta);

    void setSelected(bool selected);

    void processAction(Action action);
    
    std::vector<std::vector<WorldObject*> > objects;
    bool inRange(const sf::Vector2i& position) const;
    bool canAddObject(WorldObject* object, const sf::Vector2i& position) const;
    bool addObject(WorldObject* object, const sf::Vector2i& position);
    WorldObject* getObject(const sf::Vector2i& position) const;
private:
    bool selected;
    Game& game;

    std::list<WorldObject*> objectsAsList;
    PlayerObject* player;
};
#endif
