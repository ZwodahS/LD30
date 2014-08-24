#include "RootObject.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_conversion.hpp"
#include "DisplayManager.hpp"
#include "MainScreen.hpp"
#include "GameScreen.hpp"
#include <iostream>
RootObject::RootObject(DisplayManager& manager)
    : DisplayObject(manager), fps(nullptr), currentChild(nullptr)
{
}

RootObject::~RootObject()
{
}

bool RootObject::init(DisplayData* data)
{
    fps = manager.terminal.newWindow(manager.debugRegion);
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
    if (child == currentChild)
    {
        currentChild = nullptr;
        if (data)
        {
            if (data->type == MainScreen::OutDataType)
            {
                auto outData = static_cast<MainScreen::OutData*>(data);
                if (outData->choice == MainScreen::NewGame)
                {
                    currentChild = manager.makeGameScreen();
                    manager.putDisplay(*currentChild);
                }
                else if (outData->choice == MainScreen::Exit)
                {
                    done = true;
                }
            }
            else if (data->type == GameScreen::OutDataType)
            {
                currentChild = manager.makeMainScreen();
                manager.putDisplay(*currentChild);
            }
        }
    }
}

void RootObject::update(const sf::Time& delta)
{
    if (!currentChild)
    {
        currentChild = manager.makeMainScreen();
        manager.putDisplay(*currentChild);
    }    
}

void RootObject::draw(const sf::Time& delta)
{
    if (fps)
    {
        fps->clear(colors::General_ClearColor);
        fps->putString_xy(0, 0, zf::floatToString(1.0f / delta.asSeconds(), 2));
    }
}
