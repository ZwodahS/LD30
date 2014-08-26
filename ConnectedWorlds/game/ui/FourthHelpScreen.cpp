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
#include "FourthHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
FourthHelpScreen::FourthHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

FourthHelpScreen::~FourthHelpScreen()
{
}

bool FourthHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void FourthHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
    int line = 1;
    window->putString_row(0, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(Tutorial part 4)");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Mr.R lives near volcano");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "The volcano constantly ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "release ashes which ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "take up too much space");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "We need to clear them.");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Oh and there is food");
    window->putChar('%', sf::Color(0, 255, 0));
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Connect the line to ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "clear them.");
    line++;
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(Press Escape)", sf::Color(0, 255, 0));
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "'V' tells us how long");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "till the next eruption.");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "If only we can block it");
}

void FourthHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool FourthHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void FourthHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void FourthHelpScreen::update(const sf::Time& delta)
{
}

void FourthHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* FourthHelpScreen::getReturnValue()
{
    return nullptr;
}


