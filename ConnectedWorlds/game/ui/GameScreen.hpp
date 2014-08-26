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
#ifndef _GAME_UI_GAMESCREEN_HPP_
#define _GAME_UI_GAMESCREEN_HPP_
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "../KeyMap.hpp"
#include "../../zf/zf_term.hpp"
#include <vector>
class World;
class GameScreen : public DisplayObject
{
public:
    static const std::string OutDataType;
    enum class Result 
    {
        Victory,
        Defeat,
    };
    class OutData : public DisplayData
    {
    public:
        OutData(Result result);

        Result result;
    };

    GameScreen(DisplayManager& manager);
    ~GameScreen();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);

    bool printHelp;
private:
    float totalTime;
    bool paused;
    DisplayObject* child;
    int numActiveWorld;
    bool lasthelp;

    int currentWorld;
    /** World orders 
     *  [0][1]
     *  [3][2]
     */
    std::vector<sf::IntRect> worldRegions;
    std::vector<sf::IntRect> infoRegions;
    
    std::vector<zf::TermWindow*> infoWindows;
    // decided to split them up .
    std::vector<zf::TermWindow*> worldWindows; 
    std::vector<zf::TermWindow*> objectsWindow;
    std::vector<World*> worlds;
    zf::TermWindow* overlayWindow;

    std::vector<Action> worldActions;
    void selectWorld(int world);

    sf::Sprite arrows[4];

    OutData* result;
};
#endif
