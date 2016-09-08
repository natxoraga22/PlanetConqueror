//
//  PlanetConqueror.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 13/11/15.
//
//

#ifndef PlanetConqueror_h
#define PlanetConqueror_h


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Planet.h"
#include "SimpleAI.h"
#include "Difficulty.h"

USING_NS_CC;
using namespace cocos2d::ui;


class PlanetConqueror : public Layer, PlanetDelegate
{
private:
    Vec2 _viewOrigin;
    Size _viewSize;
    
    Button* _pauseButton;
    
    Vector<Planet*> _planets;
    SimpleAI* _ai;
    Difficulty _difficulty;
    
    // Init auxiliar methods
    virtual void initBackground();
    virtual void initPlanets();
    bool createPlanetLayout(int numberOfPlanets);
    virtual bool planetPositionIsValid(Planet* planet);
    virtual void initPauseButton();
    
    void pauseGame(Ref *sender, Widget::TouchEventType type);
    void resumeGame(Ref *sender, Widget::TouchEventType type);
    
public:
    static Scene* createGameScene(Difficulty difficulty);
    // Init code. This function is called from the create() function
    virtual bool init(Difficulty difficulty);
    
    // Planet Delegate methods
    virtual void attackablePlanetClicked(Planet *planet);
    virtual void planetOwnerChanged(Planet *planet);
    
    // implement the "static create()" method
    static PlanetConqueror* create(Difficulty difficulty);
};


#endif /* PlanetConqueror_h */
