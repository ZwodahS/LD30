#ifndef _GAME_OBJECTS_WORLDOBJECT_HPP_
#define _GAME_OBJECTS_WORLDOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include "../../zf/zf_term.hpp"
class Game;
class World;
class WorldObject 
{
public:
    enum class ObjectType
    {
        PlayerObject,
        EnvironmentObject,
    };
    WorldObject(Game& game, World& world, ObjectType type);
    ~WorldObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta) = 0;

    const ObjectType type;
    World& world;
    sf::Vector2i position;
    Game& game;
};
#endif
