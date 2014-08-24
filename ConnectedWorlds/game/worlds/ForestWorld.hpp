#ifndef _GAME_WORLDS_FORESTWORLD_HPP_
#define _GAME_WORLDS_FORESTWORLD_HPP_
#include "World.hpp"
class ForestWorld : public World
{
public:
    ForestWorld(Game& game);
    ~ForestWorld();
    
    virtual void draw(zf::TermWindow* window, zf::TermWindow* objectsWindow, zf::TermWindow* infoWindow, zf::TermWindow* overlayWindow, const sf::Time& delta);
    virtual void update(const sf::Time& delta);
};
#endif
