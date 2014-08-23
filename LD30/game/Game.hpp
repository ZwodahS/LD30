#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <list>
#include "KeyMap.hpp"
#include "../zf/zf_term.hpp"
#include "ui/DisplayManager.hpp"
#include "f_log.hpp"
class Game
{

//////////////////// Constants ////////////////////
public:
    static const int NO_KEY;
    static const int ENTER_KEY;
    static const int ESCAPE_KEY;
    static const int UP_KEY;
    static const int DOWN_KEY;
    static const int LEFT_KEY;
    static const int RIGHT_KEY;


    static const int Framerate;
    static const sf::Vector2i WorldSize;
    static const sf::Vector2i TermSize;
    // size of the individual sprite
    static const sf::Vector2i ImageSize;
    // by default we will use a cell size of 8 by 8, if the player do a 2x then we do 16 by 16
    static const std::string Title;
//////////////////// Basic stuffs ////////////////////
public:
    Game();
    ~Game();

    void init();
    void run();
private:
    void initUI();
    void initKeys();

    int cellSize;
    sf::Vector2i screenSize;

    sf::RenderWindow* renderWindow;
    zf::Terminal* terminal;

    void update(const sf::Time& delta);
    void draw(const sf::Time& delta);

//////////////////// input handling /////////////////////
public:
    int getNextKey();
    void clearKeQueue();
    KeyMap keyMap;
private:
    std::list<int> keyQueue;
//////////////////// display state manager ////////////////////
public:
private:
    DisplayManager* displayStack;
//////////////////// Assets ////////////////////
public:
    sf::Sprite getPlayerSprite(int worldId);
    sf::Sprite getCharSprite(char c);
    sf::Sprite getSpecialCharSprite(int c);
private:
    void initAssets();
};
#endif
