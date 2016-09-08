//
//  EndGameMenu.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#include "EndGameMenu.h"
#include "Resources.h"
#include "Constants.h"
#include "PlanetConqueror.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


#pragma mark - Init methods

Scene* EndGameMenu::createEndGameMenuScene(MenuType type, Difficulty difficulty)
{
    auto endGameMenuScene = Scene::create();
    
    // this will call the "init" method inside this class
    auto endGameMenuLayer = EndGameMenu::create(type, difficulty);
    
    endGameMenuScene->addChild(endGameMenuLayer);
    return endGameMenuScene;
}

EndGameMenu* EndGameMenu::create(MenuType type, Difficulty difficulty)
{
    EndGameMenu *pRet = new EndGameMenu();
    if (pRet && pRet->init(type, difficulty)) pRet->autorelease();
    else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

bool EndGameMenu::init(MenuType type, Difficulty difficulty)
{
    if (!GenericMenu::init()) return false;
    
    _difficulty = difficulty;
    
    this->initTitle(type);
    this->initButtons();
    
    if (!UserDefault::getInstance()->getBoolForKey(MUTE_KEY, false)) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(MAIN_MENU_BACKGROUND_MUSIC, true);
    }
    return true;
}

void EndGameMenu::initTitle(MenuType type)
{
    string titleString;
    switch (type) {
        case MenuType::GameOver: titleString = GAME_OVER_MENU_TITLE; break;
        case MenuType::Win: titleString = WIN_MENU_TITLE; break;
        default: titleString = ""; break;
    }
    
    auto title = Label::createWithTTF(titleString, FONT_FILE_NAME, ENDGAME_MENU_TITLE_FONT_SIZE);
    title->setAlignment(TextHAlignment::CENTER);
    title->setPosition(_viewOrigin.x + _viewSize.width/2.0, _viewOrigin.y + _viewSize.height * MENU_TITLE_Y_POSITION_RATIO);
    this->addChild(title);
}

void EndGameMenu::initButtons()
{
    // Play again button
    auto playButton = Button::create(MENU_BUTTON_FILE_NAME, "", "");
    playButton->setTitleFontName(FONT_FILE_NAME);
    playButton->setTitleText(PLAY_AGAIN_BUTTON_TITLE);
    playButton->setPosition(Vec2(_viewOrigin.x + _viewSize.width/2.0,
                                 _viewOrigin.y + _viewSize.height * PLAY_AGAIN_BUTTON_Y_POSITION_RATIO));
    playButton->setScale(_viewSize.width * MENU_BUTTON_SIZE_RATIO / playButton->getBoundingBox().size.width);
    playButton->setTitleFontSize(MENU_BUTTON_TEXT_FONT_SIZE);
    playButton->addTouchEventListener(CC_CALLBACK_2(EndGameMenu::playGame, this));
    this->addChild(playButton);
    
    // Main menu button
    auto mainMenuButton = Button::create(MENU_BUTTON_FILE_NAME, "", "");
    mainMenuButton->setTitleFontName(FONT_FILE_NAME);
    mainMenuButton->setTitleText(MAIN_MENU_BUTTON_TITLE);
    mainMenuButton->setPosition(Vec2(_viewOrigin.x + _viewSize.width/2.0,
                                     _viewOrigin.y + _viewSize.height * MAIN_MENU_BUTTON_Y_POSITION_RATIO));
    mainMenuButton->setScale(_viewSize.width * MENU_BUTTON_SIZE_RATIO / mainMenuButton->getBoundingBox().size.width);
    mainMenuButton->setTitleFontSize(MENU_BUTTON_TEXT_FONT_SIZE);
    mainMenuButton->addTouchEventListener(CC_CALLBACK_2(EndGameMenu::mainMenu, this));
    this->addChild(mainMenuButton);
}


#pragma mark - Button callbacks

void EndGameMenu::playGame(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(PlanetConqueror::createGameScene(_difficulty));
    }
}

void EndGameMenu::mainMenu(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        Director::getInstance()->replaceScene(MainMenu::createMainMenuScene(_difficulty));
    }
}
