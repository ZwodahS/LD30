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
#include "MenuPopup.hpp"
#include "DisplayManager.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
#include "../c_colors.hpp"
#include <iostream>
const std::string MenuPopup::OutDataType = "MENUPOP_OUT";
MenuPopup::OutData::OutData(MenuPopup::Choice choice, bool newTutorialMode)
    : DisplayData(OutDataType), choice(choice), tutorialMode(newTutorialMode)
{
}
const std::string MenuPopup::InDataType = "MENUPOP_IN";
MenuPopup::InData::InData(bool currentTutorialMode)
    : DisplayData(InDataType), tutorialMode(currentTutorialMode)
{
}
const int MenuPopup::NumOptions = 5;
const std::string MenuPopup::OptionsString[5] = {
    "Resume Game",
    "Configures Keys",
    "Restart Game",
    "", // need to depend on the current state of tutorial.
    "Exit to Menu",
};
const MenuPopup::Choice  MenuPopup::OptionsChoice[5] = {
    MenuPopup::Resume,
    MenuPopup::Config,
    MenuPopup::Restart,
    MenuPopup::ToggleTutorial,
    MenuPopup::Exit,
};

MenuPopup::MenuPopup(DisplayManager& manager)
    : DisplayObject(manager), mainWindow(nullptr), selected(0)
{
}

MenuPopup::~MenuPopup()
{
}

bool MenuPopup::init(DisplayData* data)
{
    if (!data || data->type != InDataType)
    {
        return false;
    }
    auto inData = static_cast<InData*>(data);
    tutorialMode = inData->tutorialMode;
    region = sf::IntRect(0, 0, 23, NumOptions + 2);
    region = zf::centerRect(region, manager.displayRegion);
    mainWindow = manager.terminal.newWindow(region);
    return true;
}

DisplayData* MenuPopup::getReturnValue()
{
    return new OutData(selected == 2 ? Restart : selected == 4 ? Exit : Resume, tutorialMode);
}

void MenuPopup::destroy()
{
    if (mainWindow)
    {
        manager.terminal.freeWindow(*mainWindow);
    }
}

bool MenuPopup::processKey(int key)
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
        if (selected == 0 || selected == 2 || selected == 4)
        {
            done = true;
        }
        else if (selected == 3)
        {
            tutorialMode = !tutorialMode;
        }
        else if (selected == 1)
        {
            child = manager.makeConfigurationScreen(manager.game.keyMap);
            manager.putDisplay(*child);
        }
        else
        {
        }
    }
    else if (action == Action::Cancel)
    {
        done = true;
        selected = 0; // force
    }
    return true;
}

void MenuPopup::childReturned(DisplayObject* child, DisplayData* data)
{
    if (child == this->child)
    {
        this->child = nullptr;
    }
}

void MenuPopup::update(const sf::Time& delta)
{
}

void MenuPopup::draw(const sf::Time& delta)
{
    mainWindow->clear(sf::Color(20, 20, 20, 255));
    mainWindow->drawEdgeBorder();
    for (int i = 0; i < NumOptions; i++)
    {
        int state = colors::Mod_Base | (i == selected ? colors::Mod_Selected : 0);
        mainWindow->putString_row(0, (i + 1), region.width, zf::TermWindow::TextAlignmentX::Center, 0, i != 3 ? OptionsString[i] : (std::string("Tutorial ") + (tutorialMode ? "On" : "Off" )) , colors::Button_Text[state]);
    }
}
