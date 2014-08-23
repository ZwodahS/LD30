#include "KeyMap.hpp"

KeyMap::KeyMap()
{
}

KeyMap::~KeyMap()
{
}

void KeyMap::addMapping(const int& c, const Action& key)
{
    auto find = keyMappings.equal_range(c);
    for (auto it = find.first; it != find.second; it++)
    {
        if ((*it).second == key)
        {
            // key-value pair already exist.
            return;
        }
    }
    keyMappings.insert(std::pair<int, Action>(c, key));
}

Action KeyMap::getMapping(const int& c) const
{
    auto find = keyMappings.find(c);
    return find != keyMappings.end() ? (*find).second : Action::None;
}

