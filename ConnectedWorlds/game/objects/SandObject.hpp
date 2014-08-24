#ifndef _GAME_OBJECTS_SANDOBJECT_HPP_
#define _GAME_OBJECTS_SANDOBJECT_HPP_
#include "WorldObject.hpp"
class SandObject : public WorldObject
{
public:
    SandObject(Game& game, World& world);
    virtual ~SandObject();

    int count;
    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
private:
    sf::Sprite sprite[4];
};
#endif
