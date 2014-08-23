#ifndef _GAME_UI_DISPLAYMANAGER_HPP_
#define _GAME_UI_DISPLAYMANAGER_HPP_
#include <list>
#include <SFML/Graphics.hpp>
#include "../../zf/zf_term.hpp"
class Game;
class DisplayObject;
class DisplayManager
{
public:
    DisplayManager(Game& game, zf::Terminal& term, const sf::IntRect& displayRegion);
    ~DisplayManager();

    Game& game;
    zf::Terminal& terminal;

    const std::list<DisplayObject*>& getDisplayObjects() const;
    void processKey(int key);
    void updateAll(const sf::Time& delta);
    void drawAll(const sf::Time& delta);
    void putDisplay(DisplayObject& state);

    const sf::IntRect displayRegion; 
    bool empty() const;
private:
    std::list<DisplayObject*> stack;
};
#endif
