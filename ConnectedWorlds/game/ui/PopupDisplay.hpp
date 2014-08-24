#ifndef _GAME_UI_POPUPDISPLAY_HPP_
#define _GAME_UI_POPUPDISPLAY_HPP_
#include "DisplayObject.hpp"
#include "DIsplayData.hpp"
#include <string>
#include "../../zf/zf_term.hpp"
class PopupDisplay : public DisplayObject
{
public:
    static const std::string InDataType;
    class InData : public DisplayData
    {
    public:
        InData(const std::string& message);

        std::string message;
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

    std::string message;
private:
    sf::IntRect region;
    zf::TermWindow* window;
};
#endif
