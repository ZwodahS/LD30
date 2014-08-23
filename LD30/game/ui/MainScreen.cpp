#include "MainScreen.hpp"

MainScreen::MainScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

MainScreen::~MainScreen()
{
}

bool MainScreen::init(DisplayData* data)
{
    return true;
}

DisplayData* MainScreen::getReturnValue()
{
    return nullptr;
}

void MainScreen::destroy()
{
}

bool MainScreen::processKey(int key)
{
    return true;
}

void MainScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void MainScreen::update(const sf::Time& delta)
{
}

void MainScreen::draw(const sf::Time& delta)
{
}
