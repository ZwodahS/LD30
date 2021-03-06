/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2013- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 */
#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <list>
#include "BalanceConfig.hpp"
#include "KeyMap.hpp"
#include "../zf/zf_term.hpp"
#include "ui/DisplayManager.hpp"
#include "f_log.hpp"
class Game
{

//////////////////// Constants ////////////////////
public:

    static const std::string RootPath;
    static const std::string Version;
    static const std::string VersionName;
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
/**
 * Should be constant but I need to calculate it on run time.
 */
    int Special_Sand1;
    int Special_Sand2;
    int Special_Sand3;
    int Special_Sand4;
    int Special_Unit;
    int Special_Volcano;
    int Special_Water;
//////////////////// Basic stuffs ////////////////////
public:
    Game();
    ~Game();

    BalanceConfig balance;

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
    sf::Sprite keyToSprite(int c);
private:
    void initAssets();
};
#endif
