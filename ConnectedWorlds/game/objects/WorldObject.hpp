#ifndef _GAME_OBJECTS_WORLDOBJECT_HPP_
#define _GAME_OBJECTS_WORLDOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include "../../zf/zf_term.hpp"
#include "../../zf/zf_direction.hpp"
class Game;
class World;
class WorldObject 
{
public:
    enum class ObjectType
    {
        PlayerObject,
        AshObject,
        FoodObject,
        WaterObject,
        SandObject,
        VolcanoObject,
        TreeObject,
    };
    WorldObject(Game& game, World& world, ObjectType type);
    virtual ~WorldObject();

    void reset();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta) = 0;
    virtual void update(const sf::Time& delta);
    virtual bool isPushable() const;
    virtual bool canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const;
    virtual bool canBeGrabbed() const;
    virtual bool grab();
    virtual void drop();

    const ObjectType type;
    World* world;
    sf::Vector2i position;
    Game& game;

    bool grabbed;

    bool markedForRemoval;
    /**
     * Used together with markedForRemoval,
     * this prevent it from being deleted. Instead it is returned to the gamescreen.
     */
    bool isSpawnElsewhere;
};
#endif
