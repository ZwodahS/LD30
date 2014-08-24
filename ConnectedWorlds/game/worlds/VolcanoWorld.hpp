#ifndef _GAME_WORLDS_VOLCANOWORLD_HPP_
#define _GAME_WORLDS_VOLCANOWORLD_HPP_
#include "World.hpp"
class VolcanoObject;
class VolcanoWorld : public World
{
public:
    VolcanoWorld(Game& game);
    ~VolcanoWorld();

    virtual void draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta);
    virtual void update(const sf::Time& delta);
private:
    VolcanoObject* volcano;
    bool erupt(int amount); // return false if not enough place to erupt
    float seconds;
};
#endif
