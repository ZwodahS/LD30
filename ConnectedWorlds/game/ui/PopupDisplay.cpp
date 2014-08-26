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
    : DisplayData(InDataType)
{
    messages.push_back(message);
}

PopupDisplay::InData::InData(const std::list<std::string>& messages)
    : DisplayData(InDataType), messages(messages)
{
}

bool PopupDisplay::init(DisplayData* data) 
{
    if (data && data->type == InDataType)
    {
        auto inData = static_cast<InData*>(data);
        messages = inData->messages;
    }
    {
        int width = 21;
        int height = 5 + messages.size();
        region = sf::IntRect(0, 0, width, height);
        region = zf::centerRect(region, manager.displayRegion);
        window = manager.terminal.newWindow(region);
        firstDraw();
    }
    return true;
}

void PopupDisplay::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder();
    int line = 1;
    for (auto message : messages)
    {
        window->putString_row(1, line++, region.width, zf::TermWindow::TextAlignmentX::Center, 0, message);
    }
    window->putString_row(1, line + 1, region.width, zf::TermWindow::TextAlignmentX::Center, 0, "(press escape)");
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
}
