#ifndef _GAME_WORLDOBJECT_HPP_
#define _GAME_WORLDOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include "../zf/zf_term.hpp"
class Game;
class WorldObject 
{
public:
    enum class ObjectType
    {
        PlayerObject,
    };
    WorldObject(Game& game, ObjectType type);
    ~WorldObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta) = 0;

    const ObjectType type;
    sf::Vector2i position;
    Game& game;
};
#endif
