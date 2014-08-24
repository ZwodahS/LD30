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


