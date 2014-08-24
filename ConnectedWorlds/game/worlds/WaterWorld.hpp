#ifndef _GAME_WORLDS_WATERWORLD_HPP_
#define _GAME_WORLDS_WATERWORLD_HPP_
#include "World.hpp"
class WaterWorld : public World
{
public:
    WaterWorld(Game& game);
    ~WaterWorld();

    virtual void draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta);
    virtual void update(const sf::Time& delta);
};
#endif
