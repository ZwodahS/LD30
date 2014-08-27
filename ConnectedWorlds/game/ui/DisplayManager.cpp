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
#include "DisplayManager.hpp"
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "MainScreen.hpp"
#include "PopupDisplay.hpp"
#include "GameScreen.hpp"
#include "RootObject.hpp"
#include "KeyConfigurationScreen.hpp"
#include "KeyChooserPopup.hpp"
#include "FirstHelpScreen.hpp"
#include "SecondHelpScreen.hpp"
#include "ThirdHelpScreen.hpp"
#include "FourthHelpScreen.hpp"
#include "LastHelpScreen.hpp"
#include <iostream>
DisplayManager::DisplayManager(Game& game, zf::Terminal& term, const sf::IntRect& displayRegion, const sf::IntRect& debugRegion)
    : game(game), terminal(term), displayRegion(displayRegion), debugRegion(debugRegion)
{
}

DisplayManager::~DisplayManager()
{
}


void DisplayManager::processKey(int key)
{
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        if ((**it).processKey(key))
        {
            break;
        }
    }
}

void DisplayManager::updateAll(const sf::Time& delta)
{
    auto display = stack.size() ? stack.back() : nullptr;
    while (display && display->done)
    {
        stack.pop_back();
        auto returnVal = display->getReturnValue();
        if (stack.size())
        {
            stack.back()->childReturned(display, returnVal);
        }
        display->destroy();
        delete display;
        delete returnVal;
        display = stack.size() ? stack.back() : nullptr;
    }
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        if (!(**it).done)
        {
            (**it).update(delta);
        }
    }
}

void DisplayManager::drawAll(const sf::Time& delta)
{
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        (**it).draw(delta);
    }
}

void DisplayManager::putDisplay(DisplayObject& object)
{
    stack.push_back(&object);
}

bool DisplayManager::empty() const
{
    return stack.size() == 0;
}

DisplayObject* DisplayManager::makeRoot()
{
    DisplayObject* object = new RootObject(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeMainScreen()
{
    DisplayObject* object = new MainScreen(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeGameScreen(bool tutorial)
{
    GameScreen* object = new GameScreen(*this);
    object->init(nullptr);
    object->printHelp = tutorial;
    return object;
}

DisplayObject* DisplayManager::makeMessagePopup(const std::string& message)
{
    DisplayObject* object = new PopupDisplay(*this);
    PopupDisplay::InData data(message);
    object->init(&data);
    return object;
}

DisplayObject* DisplayManager::makeMessagePopup(const std::list<std::string>& messages)
{
    DisplayObject* object = new PopupDisplay(*this);
    PopupDisplay::InData data(messages);
    object->init(&data);
    return object;
}

DisplayObject* DisplayManager::makeKeyChooser(const std::string& message)
{
    DisplayObject* object = new KeyChooserPopup(*this);
    KeyChooserPopup::InData data(message);
    object->init(&data);
    return object;
}

DisplayObject* DisplayManager::makeConfigurationScreen(KeyMap& mapping)
{
    DisplayObject* object = new KeyConfigurationScreen(*this);
    KeyConfigurationScreen::InData data(mapping);
    object->init(&data);
    return object;
}

DisplayObject* DisplayManager::makeFirstHelpScreen()
{
    DisplayObject* object = new FirstHelpScreen(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeSecondHelpScreen()
{
    DisplayObject* object = new SecondHelpScreen(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeThirdHelpScreen()
{
    DisplayObject* object = new ThirdHelpScreen(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeFourthHelpScreen()
{
    DisplayObject* object = new FourthHelpScreen(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeLastHelpScreen()
{
    DisplayObject* object = new LastHelpScreen(*this);
    object->init(nullptr);
    return object;
}
