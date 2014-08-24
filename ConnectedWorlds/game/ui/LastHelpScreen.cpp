#include "LastHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
LastHelpScreen::LastHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

LastHelpScreen::~LastHelpScreen()
{
}

bool LastHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void LastHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
    int line = 1;
    window->putString_row(0, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "Good luck !!");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Don't let anyone starve");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Don't get trapped.");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "There is a way to win");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(Press Escape)", sf::Color(0, 255, 0));
}

void LastHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool LastHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void LastHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void LastHelpScreen::update(const sf::Time& delta)
{
}

void LastHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* LastHelpScreen::getReturnValue()
{
    return nullptr;
}


