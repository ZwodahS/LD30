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
    DisplayManager(Game& game, zf::Terminal& term, const sf::IntRect& displayRegion, const sf::IntRect& debugRegion);
    ~DisplayManager();

    Game& game;
    zf::Terminal& terminal;

    const std::list<DisplayObject*>& getDisplayObjects() const;
    void processKey(int key);
    void updateAll(const sf::Time& delta);
    void drawAll(const sf::Time& delta);
    void putDisplay(DisplayObject& state);

    const sf::IntRect displayRegion; 
    const sf::IntRect debugRegion;
    bool empty() const;

    
    DisplayObject* makeRoot();
    DisplayObject* makeMainScreen();
    DisplayObject* makeGameScreen();
    DisplayObject* makeMessagePopup(const std::string& message);

    DisplayObject* makeFirstHelpScreen();
    DisplayObject* makeSecondHelpScreen();
    DisplayObject* makeThirdHelpScreen();
    DisplayObject* makeFourthHelpScreen();

private:
    std::list<DisplayObject*> stack;
};
#endif
