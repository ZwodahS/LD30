#include "RootObject.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_conversion.hpp"
#include "DisplayManager.hpp"
RootObject::RootObject(DisplayManager& manager)
    : DisplayObject(manager), fps(nullptr)
{
}

RootObject::~RootObject()
{
}

bool RootObject::init(DisplayData* data)
{
    auto region = manager.displayRegion;
    fps = manager.terminal.newWindow(sf::IntRect(region.left, region.top + region.height - 1 , region.width, 1));
    return true;
}

DisplayData* RootObject::getReturnValue()
{
    return nullptr;
}

void RootObject::destroy()
{
}

bool RootObject::processKey(int key)
{
    return true;
}

void RootObject::childReturned(DisplayObject* child, DisplayData* data)
{
}

void RootObject::update(const sf::Time& delta)
{
}

void RootObject::draw(const sf::Time& delta)
{
    if (fps)
    {
        fps->clear(colors::General_ClearColor);
        fps->putString_xy(0, 0, zf::floatToString(1.0f / delta.asSeconds(), 2));
    }
}
