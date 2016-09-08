//
//  MainMenu.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#ifndef MainMenu_h
#define MainMenu_h


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GenericMenu.h"
#include "Difficulty.h"

USING_NS_CC;
using namespace cocos2d::ui;


class MainMenu : public GenericMenu
{
private:
    Label* _difficulty;
    Button* _muteButton;
    bool _musicPaused;
    
    // Init auxiliar methods
    virtual void initTitle();
    virtual void initButtons();
    virtual void initDifficultyChoice(Difficulty difficulty);
    virtual void initMuteButton();
    
    void playGame(Ref *sender, Widget::TouchEventType type);
    void nextDifficulty(Ref *sender, Widget::TouchEventType type);
    void previousDifficulty(Ref *sender, Widget::TouchEventType type);
    void muteSounds(Ref *sender, Widget::TouchEventType type);
    void playSounds(Ref *sender, Widget::TouchEventType type);
    
public:
    static Scene* createMainMenuScene(Difficulty difficulty);
    static Scene* createMainMenuScene();
    // Init code. This function is called from the create() function
    virtual bool init(Difficulty difficulty);
    
    // implement the "static create()" method
    static MainMenu* create(Difficulty difficulty);
};


#endif /* MainMenu_h */
