#ifndef _GAME_WORLDS_SANDWORLD_HPP_
#define _GAME_WORLDS_SANDWORLD_HPP_
#include "World.hpp"
class SandWorld : public World
{
public:
    SandWorld(Game& game);
    ~SandWorld();

    virtual void draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta);
    virtual void update(const sf::Time& delta);
protected:
    virtual bool spawnSand() const;
};
#endif
