#ifndef _GAME_OBJECTS_FOODOBJECT_HPP_
#define _GAME_OBJECTS_FOODOBJECT_HPP_
#include "WorldObject.hpp"
class FoodObject : public WorldObject
{
public:
    FoodObject(Game& game, World& world);
    virtual ~FoodObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
private:
    sf::Sprite sprite;
    sf::Sprite grabbedBackground;
};
#endif
