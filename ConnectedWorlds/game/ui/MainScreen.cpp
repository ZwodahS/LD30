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
#include "MainScreen.hpp"
#include "DisplayManager.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
#include "../c_colors.hpp"
#include <iostream>
const std::string MainScreen::OutDataType = "MS_OUT";
const int MainScreen::NumOptions = 4;
const std::string MainScreen::OptionsString[4] = { "Play!", "Play (No tutorial)", "Change key", "Quit!" };
const MainScreen::  Choice MainScreen::OptionsChoice[4] = { MainScreen::NewGame, MainScreen::NewGame_NoTut, MainScreen::KeyConfiguration, MainScreen::Exit };

MainScreen::MainScreen(DisplayManager& manager)
    : DisplayObject(manager), mainWindow(nullptr), selected(0)
{
}

MainScreen::~MainScreen()
{
}

MainScreen::OutData::OutData(MainScreen::Choice choice)
    : DisplayData(OutDataType), choice(choice)
{
}

bool MainScreen::init(DisplayData* data)
{
    mainWindow = manager.terminal.newWindow(manager.displayRegion);
    return true;
}

DisplayData* MainScreen::getReturnValue()
{
    return new OutData(selected == 0 ? NewGame : selected == 1 ? NewGame_NoTut : selected == 2 ? KeyConfiguration : Exit); 
}

void MainScreen::destroy()
{
    if (mainWindow)
    {
        manager.terminal.freeWindow(*mainWindow);
    }
}

bool MainScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Up || action == Action::World_Up)
    {
        selected = selected <= 0 ? 0 : selected >= NumOptions ? NumOptions - 1 : selected - 1;
    }
    else if (action == Action::Down || action == Action::World_Down)
    {
        selected = selected < 0 ? 0 : selected >= NumOptions - 1 ? NumOptions - 1 : selected + 1;
    }
    else if (action == Action::Select)
    {
        done = true;
    }
    return true;
}

void MainScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void MainScreen::update(const sf::Time& delta)
{
}

void MainScreen::draw(const sf::Time& delta)
{
    mainWindow->putString_row(0, 8, manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Center, 0, "We are Connected...");
    mainWindow->putString_row(0, manager.displayRegion.top + manager.displayRegion.width - 2, manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Center, 0, manager.game.Version + "("+manager.game.VersionName+")");
    mainWindow->putString_row(0, manager.displayRegion.top + manager.displayRegion.width - 1, manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Center, 0, "By ZwodahS");
    for (int i = 0; i < NumOptions; i++)
    {
        int state = colors::Mod_Base | (i == selected ? colors::Mod_Selected : 0);
        mainWindow->putString_row(0, 15 + (i * 2), manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Center, 0, OptionsString[i], colors::Button_Text[state]);
    }
}
