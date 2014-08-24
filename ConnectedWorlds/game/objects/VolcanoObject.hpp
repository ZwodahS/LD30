#ifndef _GAME_OBJECTS_VOLCANOOBJECT_HPP_
#define _GAME_OBJECTS_VOLCANOOBJECT_HPP_
#include "WorldObject.hpp"
class VolcanoObject : public WorldObject
{
public:
    VolcanoObject(Game& game, World& world);
    virtual ~VolcanoObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
    virtual bool canPush(zf::Direction) const;
    virtual bool canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const;
    virtual bool canBeGrabbed() const;

    int time;
private:
    sf::Sprite background;
    sf::Sprite sprite;
};
#endif
