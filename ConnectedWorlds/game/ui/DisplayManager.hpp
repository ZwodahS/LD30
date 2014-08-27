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
#ifndef _GAME_UI_DISPLAYMANAGER_HPP_
#define _GAME_UI_DISPLAYMANAGER_HPP_
#include <list>
#include <SFML/Graphics.hpp>
#include "../../zf/zf_term.hpp"
class Game;
class KeyMap;
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
    DisplayObject* makeGameScreen(bool tutorial = true);
    DisplayObject* makeMessagePopup(const std::string& message);
    DisplayObject* makeMessagePopup(const std::list<std::string>& messages);
    DisplayObject* makeConfigurationScreen(KeyMap& mapping);
    DisplayObject* makeKeyChooser(const std::string& message);

    DisplayObject* makeFirstHelpScreen();
    DisplayObject* makeSecondHelpScreen();
    DisplayObject* makeThirdHelpScreen();
    DisplayObject* makeFourthHelpScreen();
    DisplayObject* makeLastHelpScreen();
private:
    std::list<DisplayObject*> stack;
};
#endif
