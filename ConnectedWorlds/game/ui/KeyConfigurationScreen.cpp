#include "KeyConfigurationScreen.hpp"
#include "KeyChooserPopup.hpp"
#include "DisplayManager.hpp"
#include "../Game.hpp"
#include "../c_colors.hpp"
const std::string KeyConfigurationScreen::InDataType = "KCS_IN";
const Action KeyConfigurationScreen::MappableActions[] = {
            Action::Up, Action::Down, Action::Left, Action::Right,
            Action::World_Up, Action::World_Down, Action::World_Left, Action::World_Right,
            Action::World_1, Action::World_2, Action::World_3, Action::World_4
};
const std::string KeyConfigurationScreen::ActionStrings[] = {
            "Move up", "Move down", "Move left", "Move right", 
            "World up", "World down", "World left", "World right",
            "Select World 1", "Select World 2", "Select World 3", "Select World 4"
};
KeyConfigurationScreen::KeyConfigurationScreen(DisplayManager& manager)
    : DisplayObject(manager), mainWindow(nullptr), selected(0), child(nullptr)
{
}

KeyConfigurationScreen::~KeyConfigurationScreen()
{
}

KeyConfigurationScreen::InData::InData(KeyMap& mapping)
    : DisplayData(InDataType), mapping(mapping)
{
}

bool KeyConfigurationScreen::init(DisplayData* data)
{
    if (!data || data->type != InDataType)
    {
        return false;
    }
    keyMap = &static_cast<InData*>(data)->mapping;
    mainWindow = manager.terminal.newWindow(manager.displayRegion);
    return true;
}

DisplayData* KeyConfigurationScreen::getReturnValue()
{
    return nullptr;
}

void KeyConfigurationScreen::destroy()
{
    if (mainWindow)
    {
        manager.terminal.freeWindow(*mainWindow);
    }
}

bool KeyConfigurationScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Up || action == Action::World_Up)
    {
        selected = selected <= 0 ? 0 : selected >= NumOptions ? NumOptions - 1 : selected - 1;
    }
    else if (action == Action::Down || action == Action::World_Down)
    {
        selected = selected < 0 ? 0 : selected >= NumOptions - 1 ? NumOptions - 1 : selected + 1;
    }
    else if (action == Action::Select)
    {
        if (selected != NumOptions - 1)
        {
            child = manager.makeKeyChooser("Enter Key");
            manager.putDisplay(*child);
        }
        else 
        {
            done = true;
        }
    }
    else if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void KeyConfigurationScreen::childReturned(DisplayObject* child, DisplayData* data)
{
    if (this->child == child)
    {
        if (data && data->type == KeyChooserPopup::OutDataType)
        {
            auto chosenKey = static_cast<KeyChooserPopup::OutData*>(data)->chosenKey;
            if (chosenKey != -1)
            {
                keyMap->addMapping(chosenKey, MappableActions[selected]);
            }
        }
    }
}

void KeyConfigurationScreen::update(const sf::Time& delta)
{
}

void KeyConfigurationScreen::draw(const sf::Time& delta)
{
    mainWindow->clear(sf::Color(20, 20, 20, 255));
    for (int i = 0; i < NumOptions - 1; i++)
    {
        int state = colors::Mod_Base | (i == selected ? colors::Mod_Selected : 0);
        mainWindow->putString_row(2, 3 + i, manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Left, 0, ActionStrings[i], colors::Button_Text[state]);
        mainWindow->putSprite_xyf(manager.displayRegion.width - 2, 3 + i, zf::setCopyColor(manager.game.keyToSprite(keyMap->getKey(MappableActions[i])), colors::Button_Text[state]));
    }
    mainWindow->putString_row(0, 3 + NumOptions + 1, manager.displayRegion.width, zf::TermWindow::TextAlignmentX::Center, 0, "Exit Config", colors::Button_Text[colors::Mod_Base | (NumOptions-1 == selected ? colors::Mod_Selected : 0)]);
}
