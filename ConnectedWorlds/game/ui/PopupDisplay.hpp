#ifndef _GAME_UI_POPUPDISPLAY_HPP_
#define _GAME_UI_POPUPDISPLAY_HPP_
#include "DisplayObject.hpp"
#include "DIsplayData.hpp"
#include <string>
#include "../../zf/zf_term.hpp"
#include <list>
class PopupDisplay : public DisplayObject
{
public:
    static const std::string InDataType;
    class InData : public DisplayData
    {
    public:
        InData(const std::string& message);
        InData(const std::list<std::string>& messages);

        std::list<std::string> messages;
    };
    PopupDisplay(DisplayManager& manager);
    ~PopupDisplay();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);

    std::list<std::string> messages;
private:
    sf::IntRect region;
    zf::TermWindow* window;
    void firstDraw();
};
#endif
