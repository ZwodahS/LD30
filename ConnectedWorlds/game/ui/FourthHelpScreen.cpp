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


