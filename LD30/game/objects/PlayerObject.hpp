#ifndef _GAME_OBJECTS_PLAYEROBJECT_HPP_
#define _GAME_OBJECTS_PLAYEROBJECT_HPP_
#include "WorldObject.hpp"
class PlayerObject : public WorldObject
{
public:
    PlayerObject(Game& game, World& world);
    virtual ~PlayerObject();

    void draw(zf::TermWindow* window, const sf::Time& delta);
    bool canPush(zf::Direction direction);
private:
    sf::Sprite sprite;
};
#endif
