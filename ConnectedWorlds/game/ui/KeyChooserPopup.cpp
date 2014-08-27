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
#include "KeyChooserPopup.hpp"
#include "DisplayManager.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
#include "../c_colors.hpp"
const std::string KeyChooserPopup::InDataType = "KCP_IN";
const std::string KeyChooserPopup::OutDataType = "KCP_OUT";

KeyChooserPopup::KeyChooserPopup(DisplayManager& manager)
    : DisplayObject(manager)
{
}

KeyChooserPopup::~KeyChooserPopup()
{
}

KeyChooserPopup::InData::InData(const std::string& message)
    : DisplayData(InDataType), message(message)
{
}

KeyChooserPopup::OutData::OutData(int k)
    : DisplayData(OutDataType), chosenKey(k)
{
}

bool KeyChooserPopup::init(DisplayData* data) 
{
    if (data->type == InDataType)
    {
        message = static_cast<InData*>(data)->message;
    }
    {
        int width = 21;
        int height = 5;
        region = sf::IntRect(0, 0, width, height);
        region = zf::centerRect(region, manager.displayRegion);
        window = manager.terminal.newWindow(region);
        firstDraw();
    }
    return true;
}

void KeyChooserPopup::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder();
    int line = 1;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, message);
    window->putString_row(1, line + 1, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(ESC to cancel)");
}

DisplayData* KeyChooserPopup::getReturnValue()
{
    return new OutData(chosenKey);
}

void KeyChooserPopup::destroy()
{
    manager.terminal.freeWindow(*window);
}

bool KeyChooserPopup::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        chosenKey = -1;
        done = true;
    }
    else if (action == Action::Select)
    {
    }
    else
    {
        if ( (key >= 32 && key <= 126) || (key == Game::UP_KEY) || (key == Game::DOWN_KEY) || (key == Game::LEFT_KEY) || (key == Game::RIGHT_KEY))
        {
            chosenKey = key;
            done = true;
        }
    }
    return true;
}

void KeyChooserPopup::childReturned(DisplayObject* child, DisplayData* data)
{
}

void KeyChooserPopup::update(const sf::Time& delta)
{
}

void KeyChooserPopup::draw(const sf::Time& delta)
{
}

