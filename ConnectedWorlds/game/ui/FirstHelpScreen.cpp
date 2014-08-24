#include "FirstHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../../zf/zf_sprite.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
FirstHelpScreen::FirstHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

FirstHelpScreen::~FirstHelpScreen()
{
}

bool FirstHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 2, display.top + 2, display.width - 4, display.height - 4);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void FirstHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
    int line = 1;
    window->putString_row(0, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(Tutorial part 1)");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Mr.Y is stuck in the sand");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "world. There is nothing ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "here except sand. ");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Perhaps we can do ");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "something with them.");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "I will need to find");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "food soon .");
    line++;
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(WASD) to move your unit");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(Space) to grab object.");
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "Push the sand blocks");
    window->putSprite_f(zf::setCopyColor(manager.game.getSpecialCharSprite(manager.game.Special_Sand1), sf::Color(255, 255, 0)));
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "together to merge them");
    line++;
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "(Press Escape)", sf::Color(0, 255, 0));
    line++;
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "The 'F' value is the");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "food value. It is used");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "when you move and push");
    window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Left, 0, "things.");
}

void FirstHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool FirstHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void FirstHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void FirstHelpScreen::update(const sf::Time& delta)
{
}

void FirstHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* FirstHelpScreen::getReturnValue()
{
    return nullptr;
}

