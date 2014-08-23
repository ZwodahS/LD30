#ifndef _GAME_UI_DISPLAYDATA_HPP_
#define _GAME_UI_DISPLAYDATA_HPP_
#include <string>
class DisplayData
{
public:
    DisplayData(const std::string& type);
    virtual ~DisplayData();

    const std::string type;
};
#endif
