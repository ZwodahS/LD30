#include "MainScreen.hpp"
#include "DisplayManager.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
#include "../c_colors.hpp"
#include <iostream>
const std::string MainScreen::OutDataType = "MS_OUT";
const int MainScreen::NumOptions = 2;
const std::string MainScreen::OptionsString[2] = { "Play!", "Quit!" };
const MainScreen::  Choice MainScreen::OptionsChoice[2] = { MainScreen::NewGame, MainScreen::Exit };

MainScreen::MainScreen(DisplayManager& manager)
    : DisplayObject(manager), mainWindow(nullptr), selected(0)
{
}

MainScreen::~MainScreen()
{
}

MainScreen::OutData::OutData(MainScreen::Choice choice)
    : DisplayData(OutDataType), choice(choice)
{
}

bool MainScreen::init(DisplayData* data)
{
    mainWindow = manager.terminal.newWindow(manager.displayRegion);
    {   // calculate the space needed by the buttons
        int totalSizeRequired(0);

        for (int i = 0; i < NumOptions; i++)
        {
            totalSizeRequired += OptionsString[i].size();
            totalSizeRequired += 2; // add 2 for border.
        }
        auto terminalSize = manager.terminal.getTermBound();
        int spaceAvailable = terminalSize.width - totalSizeRequired;
        int maxSpaceBetweenButton = spaceAvailable / (NumOptions - 1);
        int spaceBetweenButton = maxSpaceBetweenButton > 5 ? 5 : maxSpaceBetweenButton;
        int spaceUsed = spaceBetweenButton * (NumOptions - 1);
        int leftBegin = (spaceAvailable - spaceUsed) / 2;
        int x = leftBegin;
        for (int i = 0; i < NumOptions; i++)
        {
            buttonRegions.push_back(sf::IntRect(x, 15, OptionsString[i].size() + 2, 3));
            x += buttonRegions[i].width + spaceBetweenButton;
        }
    }
    return true;
}

DisplayData* MainScreen::getReturnValue()
{
    return new OutData(selected == 0 ? NewGame : Exit); 
}

void MainScreen::destroy()
{
    if (mainWindow)
    {
        manager.terminal.freeWindow(*mainWindow);
    }
}

bool MainScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Left || action == Action::World_Left)
    {
        selected = selected <= 0 ? 0 : selected >= NumOptions ? NumOptions - 1 : selected - 1;
    }
    else if (action == Action::Right || action == Action::World_Right)
    {
        selected = selected < 0 ? 0 : selected >= NumOptions - 1 ? NumOptions - 1 : selected + 1;
    }
    else if (action == Action::Select)
    {
        done = true;
    }
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
    mainWindow->putString_row(0, 8, manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Center, 0, "Grow");
    for (int i = 0; i < NumOptions; i++)
    {
        int state = colors::Mod_Base | (i == selected ? colors::Mod_Selected : 0);
        mainWindow->drawCenterBox(buttonRegions[i], colors::Button_Border[state]);
        mainWindow->putString_xy(buttonRegions[i].left + 1, buttonRegions[i].top + 1, OptionsString[i], colors::Button_Text[state]);
    }
}
