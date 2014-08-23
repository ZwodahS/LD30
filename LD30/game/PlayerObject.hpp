#ifndef _GAME_PLAYEROBJECT_HPP_
#define _GAME_PLAYEROBJECT_HPP_
#include "WorldObject.hpp"
class PlayerObject : public WorldObject
{
public:
    PlayerObject(Game& game, int worldId);
    ~PlayerObject();

    void draw(zf::TermWindow* window, const sf::Time& delta);
private:
    sf::Sprite sprite;
};
#endif
