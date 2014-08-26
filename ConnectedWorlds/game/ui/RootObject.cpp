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
#include "RootObject.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_conversion.hpp"
#include "DisplayManager.hpp"
#include "MainScreen.hpp"
#include "GameScreen.hpp"
#include <iostream>
RootObject::RootObject(DisplayManager& manager)
    : DisplayObject(manager), fps(nullptr), currentChild(nullptr)
{
}

RootObject::~RootObject()
{
}

bool RootObject::init(DisplayData* data)
{
#ifndef NODEBUG
    fps = manager.terminal.newWindow(manager.debugRegion);
#endif
    return true;
}

DisplayData* RootObject::getReturnValue()
{
    return nullptr;
}

void RootObject::destroy()
{
}

bool RootObject::processKey(int key)
{
    return true;
}

void RootObject::childReturned(DisplayObject* child, DisplayData* data)
{
    if (child == currentChild)
    {
        currentChild = nullptr;
        if (data)
        {
            if (data->type == MainScreen::OutDataType)
            {
                auto outData = static_cast<MainScreen::OutData*>(data);
                if (outData->choice == MainScreen::NewGame)
                {
                    currentChild = manager.makeGameScreen();
                    manager.putDisplay(*currentChild);
                }
                else if (outData->choice == MainScreen::NewGame_NoTut)
                {
                    currentChild = manager.makeGameScreen(false);
                    manager.putDisplay(*currentChild);
                }
                else if (outData->choice == MainScreen::Exit)
                {
                    done = true;
                }
            }
            else if (data->type == GameScreen::OutDataType)
            {
                currentChild = manager.makeMainScreen();
                manager.putDisplay(*currentChild);
            }
        }
    }
}

void RootObject::update(const sf::Time& delta)
{
    if (!currentChild)
    {
        currentChild = manager.makeMainScreen();
        manager.putDisplay(*currentChild);
    }    
}

void RootObject::draw(const sf::Time& delta)
{
    if (fps)
    {
        fps->clear(colors::General_ClearColor);
        fps->putString_xy(0, 0, zf::floatToString(1.0f / delta.asSeconds(), 2));
    }
}
