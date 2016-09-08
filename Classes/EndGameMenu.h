//
//  EndGameMenu.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#ifndef EndGameMenu_h
#define EndGameMenu_h


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GenericMenu.h"
#include "Difficulty.h"

USING_NS_CC;
using namespace cocos2d::ui;


enum class MenuType {
    GameOver = 0,
    Win = 1
};


class EndGameMenu : public GenericMenu
{
private:
    Difficulty _difficulty;
    
    // Init auxiliar methods
    virtual void initTitle(MenuType type);
    virtual void initButtons();
    
    void playGame(Ref *sender, Widget::TouchEventType type);
    void mainMenu(Ref *sender, Widget::TouchEventType type);
    
public:
    static Scene* createEndGameMenuScene(MenuType type, Difficulty difficulty);
    // Init code. This function is called from the create() function
    virtual bool init(MenuType type, Difficulty difficulty);
    
    // implement the "static create()" method
    static EndGameMenu* create(MenuType type, Difficulty difficulty);
};



#endif /* EndGameMenu_h */
