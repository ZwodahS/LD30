#include "ThirdHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
ThirdHelpScreen::ThirdHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

ThirdHelpScreen::~ThirdHelpScreen()
{
}

bool ThirdHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void ThirdHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
    int line = 1;
    window->putString_row(0, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(Tutorial part 3)");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Mr.G lives in the");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "forest world. There is");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "a seed here but it ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "refuses to grow. ");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Oh ! It is raining !! ");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "The seed have 5 stages");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(");
    window->putChar('.', sf::Color(0, 255, 0));
    window->putChar(',', sf::Color(0, 255, 0));
    window->putChar('i', sf::Color(0, 255, 0));
    window->putChar('t', sf::Color(0, 255, 0));
    window->putChar('T', sf::Color(0, 255, 0));
    window->putString(")");
    line++;
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(Press Escape)");
}

void ThirdHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool ThirdHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void ThirdHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void ThirdHelpScreen::update(const sf::Time& delta)
{
}

void ThirdHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* ThirdHelpScreen::getReturnValue()
{
    return nullptr;
}


