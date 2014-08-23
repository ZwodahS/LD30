#ifndef _GAME_KEYMAP_HPP_
#define _GAME_KEYMAP_HPP_
#include <map>
#include <vector>
#include <string>
enum class Action
{
    None,
    Up,
    Left,
    Right,
    Down,
    Select,
    Cancel,
};

namespace actions
{
    static const Action NavigationAction[4] = { Action::Up, Action::Down, Action::Left, Action::Right };
}

class KeyMap
{
public:
    KeyMap();
    ~KeyMap();

    /**
     * If category is "" 
     */
    void addMapping(const int& c, const Action& key);

    Action getMapping(const int& c) const;

private:
    std::map<int, Action> keyMappings;
};
#endif
