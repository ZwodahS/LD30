#include "PopupDisplay.hpp"
#include "DisplayManager.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
#include "../c_colors.hpp"
const std::string PopupDisplay::InDataType = "PD_IN";

PopupDisplay::PopupDisplay(DisplayManager& manager)
    : DisplayObject(manager)
{
}

PopupDisplay::~PopupDisplay()
{
}

PopupDisplay::InData::InData(const std::string& message)
    : DisplayData(InDataType), message(message)
{
}

bool PopupDisplay::init(DisplayData* data) 
{
    if (data && data->type == InDataType)
    {
        auto inData = static_cast<InData*>(data);
        message = inData->message;
    }
    else
    {
        message = "";
    }
    {
        int width = 19;
        int height = 5;
        region = sf::IntRect(0, 0, width, height);
        region = zf::centerRect(region, manager.displayRegion);
        window = manager.terminal.newWindow(region);
    }
    return true;
}

DisplayData* PopupDisplay::getReturnValue()
{
    return nullptr;
}

void PopupDisplay::destroy()
{
    manager.terminal.freeWindow(*window);
}

bool PopupDisplay::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void PopupDisplay::childReturned(DisplayObject* child, DisplayData* data)
{
}

void PopupDisplay::update(const sf::Time& delta)
{
}

void PopupDisplay::draw(const sf::Time& delta)
{
    // we might only need to draw once, since it is cached in the window.
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder();
    window->putString_row(1, 1, region.width, zf::TermWindow::TextAlignmentX::Center, 0, message);
    window->putString_row(1, 3, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(press escape)");
}
