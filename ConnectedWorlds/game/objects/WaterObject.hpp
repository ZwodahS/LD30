#ifndef _GAME_OBJECTS_WATEROBJECT_HPP_
#define _GAME_OBJECTS_WATEROBJECT_HPP_
#include "WorldObject.hpp"
class WaterObject : public WorldObject
{
public:
    static int ProbabilityGrowth;
    WaterObject(Game& game, World& world);
    virtual ~WaterObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
    virtual void update(const sf::Time& delta);
    bool flood;
    int floodMeter; // when it reach 10 it will flood
    virtual bool isPushable() const;
private:
    float timePassed;
    sf::Sprite sprite;
    sf::Sprite background;
};
#endif
