#ifndef _GAME_OBJECTS_PLAYEROBJECT_HPP_
#define _GAME_OBJECTS_PLAYEROBJECT_HPP_
#include "WorldObject.hpp"
class PlayerObject : public WorldObject
{
public:
    PlayerObject(Game& game, World& world);
    virtual ~PlayerObject();

    void draw(zf::TermWindow* window, const sf::Time& delta);
    bool canPush(zf::Direction direction) const;

    bool isGrabbing() const;
    /**
     * If the player is already holding things, they will be dropped.
     * If no, then it willl grab surrounding things.
     */
    void toggleGrab();
    int food;
    int work;

    const std::vector<WorldObject*>& getGrabbedObjects() const;
private:
    sf::Sprite sprite;
    std::vector<WorldObject*> grabbedObjects;
};
#endif
