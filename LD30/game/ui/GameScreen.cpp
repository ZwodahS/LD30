#include "GameScreen.hpp"
#include "../Game.hpp"
GameScreen::GameScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

GameScreen::~GameScreen()
{
}

bool GameScreen::init(DisplayData* data)
{
    return true;
}

DisplayData* GameScreen::getReturnValue()
{
    return nullptr;
}

void GameScreen::destroy()
{
}

bool GameScreen::processKey(int key)
{
    return true;
}

void GameScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void GameScreen::update(const sf::Time& delta)
{
}

void GameScreen::draw(const sf::Time& delta)
{
}
