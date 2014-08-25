#ifndef _GAME_UI_MAINSCREEN_HPP_
#define _GAME_UI_MAINSCREEN_HPP_
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "../../zf/zf_term.hpp"
#include <vector>
class MainScreen : public DisplayObject
{
public:
    static const std::string OutDataType;
    enum Choice
    {
        NewGame,
        NewGame_NoTut,
        Exit,
    };
    class OutData : public DisplayData
    {
    public:
        OutData(Choice choice);

        Choice choice;
    };

    MainScreen(DisplayManager& manager);
    ~MainScreen();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);

    static const int NumOptions;
    static const std::string OptionsString[3];
    static const Choice OptionsChoice[3];

    int selected;
private:
    zf::TermWindow* mainWindow;
};
#endif
