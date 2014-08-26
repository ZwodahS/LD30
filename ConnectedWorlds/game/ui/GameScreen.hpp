#ifndef _GAME_UI_GAMESCREEN_HPP_
#define _GAME_UI_GAMESCREEN_HPP_
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "../KeyMap.hpp"
#include "../../zf/zf_term.hpp"
#include <vector>
class World;
class GameScreen : public DisplayObject
{
public:
    static const std::string OutDataType;
    enum class Result 
    {
        Victory,
        Defeat,
    };
    class OutData : public DisplayData
    {
    public:
        OutData(Result result);

        Result result;
    };

    GameScreen(DisplayManager& manager);
    ~GameScreen();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);

    bool printHelp;
private:
    float totalTime;
    bool paused;
    DisplayObject* child;
    int numActiveWorld;
    bool lasthelp;

    int currentWorld;
    /** World orders 
     *  [0][1]
     *  [3][2]
     */
    std::vector<sf::IntRect> worldRegions;
    std::vector<sf::IntRect> infoRegions;
    
    std::vector<zf::TermWindow*> infoWindows;
    // decided to split them up .
    std::vector<zf::TermWindow*> worldWindows; 
    std::vector<zf::TermWindow*> objectsWindow;
    std::vector<World*> worlds;
    zf::TermWindow* overlayWindow;

    std::vector<Action> worldActions;
    void selectWorld(int world);

    sf::Sprite arrows[4];

    OutData* result;
};
#endif
