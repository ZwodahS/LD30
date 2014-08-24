#include "SecondHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
SecondHelpScreen::SecondHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

SecondHelpScreen::~SecondHelpScreen()
{
}

bool SecondHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void SecondHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
    int line = 1;
    window->putString_row(0, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(Tutorial part 2)");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Mr.B is stuck in the");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "water world. ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "The water look scary");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "and why is there a sand");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "here ?");
    line++;
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(");
    window->putSprite_f(manager.game.getSpecialCharSprite(zf::Arrow[zf::Left]));
    window->putSprite_f(manager.game.getSpecialCharSprite(zf::Arrow[zf::Up]));
    window->putSprite_f(manager.game.getSpecialCharSprite(zf::Arrow[zf::Right]));
    window->putSprite_f(manager.game.getSpecialCharSprite(zf::Arrow[zf::Down]));
    window->putString(") or (1234)");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "to switch world.");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Push the sand block");
    window->putSprite_f(zf::setCopyColor(manager.game.getSpecialCharSprite(manager.game.Special_Sand1), sf::Color(255, 255, 0)));
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "into the water");
    window->putSprite_f(zf::setCopyColor(manager.game.getSpecialCharSprite(manager.game.Special_Water), sf::Color(0, 0, 255)));
    line++;
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(Press Escape)");
}

void SecondHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool SecondHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void SecondHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void SecondHelpScreen::update(const sf::Time& delta)
{
}

void SecondHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* SecondHelpScreen::getReturnValue()
{
    return nullptr;
}


