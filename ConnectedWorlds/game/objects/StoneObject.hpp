#ifndef _GAME_OBJECTS_STONEOBJECT_HPP_
#define _GAME_OBJECTS_STONEOBJECT_HPP_
#include "WorldObject.hpp"
class StoneObject : public WorldObject
{
public:
    StoneObject(Game& game, World& world);
    virtual ~StoneObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
    bool canBeGrabbed() const;
private:
    sf::Sprite background;
    sf::Sprite sprite;
};
#endif
