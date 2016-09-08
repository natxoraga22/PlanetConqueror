//
//  MainMenu.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#include "MainMenu.h"
#include "Resources.h"
#include "Constants.h"
#include "PlanetConqueror.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


#pragma mark - Init methods

Scene* MainMenu::createMainMenuScene(Difficulty difficulty)
{
    auto mainMenuScene = Scene::create();
    
    // this will call the "init" method inside this class
    auto mainMenuLayer = MainMenu::create(difficulty);
    
    mainMenuScene->addChild(mainMenuLayer);
    return mainMenuScene;
}

Scene* MainMenu::createMainMenuScene()
{
    return MainMenu::createMainMenuScene(Difficulty::Medium);
}

MainMenu* MainMenu::create(Difficulty difficulty)
{
    MainMenu *pRet = new MainMenu();
    if (pRet && pRet->init(difficulty)) pRet->autorelease();
    else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

bool MainMenu::init(Difficulty difficulty)
{
    if (!GenericMenu::init()) return false;

    this->initTitle();
    this->initButtons();
    this->initDifficultyChoice(difficulty);
    this->initMuteButton();
    
    if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() && !UserDefault::getInstance()->getBoolForKey(MUTE_KEY, false)) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(MAIN_MENU_BACKGROUND_MUSIC, true);
    }
    _musicPaused = false;
    
    return true;
}

void MainMenu::initTitle()
{
    // Game title
    auto title = Label::createWithTTF(GAME_TITLE, FONT_FILE_NAME, MAIN_MENU_GAME_TITLE_FONT_SIZE);
    title->setAlignment(TextHAlignment::CENTER);
    title->setPosition(_viewOrigin.x + _viewSize.width/2.0, _viewOrigin.y + _viewSize.height * MENU_TITLE_Y_POSITION_RATIO);
    this->addChild(title);
}

void MainMenu::initButtons()
{
    // Play game button
    auto button = Button::create(MENU_BUTTON_FILE_NAME, "", "");
    button->setTitleFontName(FONT_FILE_NAME);
    button->setTitleText(PLAY_BUTTON_TITLE);
    button->setPosition(Vec2(_viewOrigin.x + _viewSize.width/2.0, _viewOrigin.y + _viewSize.height * PLAY_BUTTON_Y_POSITION_RATIO));
    button->setScale(_viewSize.width * MENU_BUTTON_SIZE_RATIO / button->getBoundingBox().size.width);
    button->setTitleFontSize(MENU_BUTTON_TEXT_FONT_SIZE);
    button->addTouchEventListener(CC_CALLBACK_2(MainMenu::playGame, this));
    this->addChild(button);
}

void MainMenu::initDifficultyChoice(Difficulty difficulty)
{
    // Difficulty label
    string title;
    switch (difficulty) {
        case Difficulty::Easy: title = EASY_DIFFICULTY_TITLE; break;
        case Difficulty::Medium: title = MEDIUM_DIFFICULTY_TITLE; break;
        case Difficulty::Hard: title = HARD_DIFFICULTY_TITLE; break;
    }
    _difficulty = Label::createWithTTF(title, FONT_FILE_NAME, MAIN_MENU_DIFFICULTY_FONT_SIZE);
    _difficulty->setAlignment(TextHAlignment::CENTER);
    _difficulty->setPosition(_viewOrigin.x + _viewSize.width/2.0, _viewOrigin.y + _viewSize.height * DIFFICULTY_Y_POSITION_RATIO);
    this->addChild(_difficulty);
    
    // Next difficulty button
    auto nextButton = Button::create(NEXT_BUTTON_FILE_NAME, "", "");
    nextButton->setPosition(Vec2(_viewOrigin.x + _viewSize.width * 2.0/3.0,
                                 _viewOrigin.y + _viewSize.height * DIFFICULTY_Y_POSITION_RATIO));
    nextButton->setScale(_viewSize.width * NEXT_BUTTON_SIZE_RATIO / nextButton->getBoundingBox().size.width);
    nextButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::nextDifficulty, this));
    this->addChild(nextButton);
    
    // Previous difficulty button
    auto previousButton = Button::create(NEXT_BUTTON_FILE_NAME, "", "");
    previousButton->setFlippedX(true);
    previousButton->setPosition(Vec2(_viewOrigin.x + _viewSize.width * 1.0/3.0,
                                 _viewOrigin.y + _viewSize.height * DIFFICULTY_Y_POSITION_RATIO));
    previousButton->setScale(_viewSize.width * NEXT_BUTTON_SIZE_RATIO / previousButton->getBoundingBox().size.width);
    previousButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::previousDifficulty, this));
    this->addChild(previousButton);
}

void MainMenu::initMuteButton()
{
    bool mute = UserDefault::getInstance()->getBoolForKey(MUTE_KEY, false);
    if (!mute) {
        _muteButton = Button::create(SOUND_BUTTON_FILE_NAME, "", "");
        _muteButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::muteSounds, this));
    }
    else {
        _muteButton = Button::create(MUTE_BUTTON_FILE_NAME, "", "");
        _muteButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::playSounds, this));
    }
    _muteButton->setAnchorPoint(Vec2(0.0, 0.0));
    _muteButton->setPosition(Vec2(_viewOrigin.x + _viewSize.width * MUTE_BUTTON_OFFSET_RATIO,
                                 _viewOrigin.y + _viewSize.width * MUTE_BUTTON_OFFSET_RATIO));
    _muteButton->setScale(_viewSize.width * MUTE_BUTTON_SIZE_RATIO / _muteButton->getBoundingBox().size.width);
    this->addChild(_muteButton);
}


#pragma mark - Button callbacks

void MainMenu::playGame(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if (_difficulty->getString() == EASY_DIFFICULTY_TITLE)
            Director::getInstance()->replaceScene(PlanetConqueror::createGameScene(Difficulty::Easy));
        else if (_difficulty->getString() == MEDIUM_DIFFICULTY_TITLE)
            Director::getInstance()->replaceScene(PlanetConqueror::createGameScene(Difficulty::Medium));
        else if (_difficulty->getString() == HARD_DIFFICULTY_TITLE)
            Director::getInstance()->replaceScene(PlanetConqueror::createGameScene(Difficulty::Hard));
    }
}

void MainMenu::nextDifficulty(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if (_difficulty->getString() == EASY_DIFFICULTY_TITLE) _difficulty->setString(MEDIUM_DIFFICULTY_TITLE);
        else if (_difficulty->getString() == MEDIUM_DIFFICULTY_TITLE) _difficulty->setString(HARD_DIFFICULTY_TITLE);
    }
}

void MainMenu::previousDifficulty(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if (_difficulty->getString() == HARD_DIFFICULTY_TITLE) _difficulty->setString(MEDIUM_DIFFICULTY_TITLE);
        else if (_difficulty->getString() == MEDIUM_DIFFICULTY_TITLE) _difficulty->setString(EASY_DIFFICULTY_TITLE);
    }
}

void MainMenu::muteSounds(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey(MUTE_KEY, true);
        _musicPaused = true;
        
        _muteButton->loadTextureNormal(MUTE_BUTTON_FILE_NAME);
        _muteButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::playSounds, this));
    }
}

void MainMenu::playSounds(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if (_musicPaused) {
            SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            _musicPaused = false;
        }
        else SimpleAudioEngine::getInstance()->playBackgroundMusic(MAIN_MENU_BACKGROUND_MUSIC);
        UserDefault::getInstance()->setBoolForKey(MUTE_KEY, false);
        
        _muteButton->loadTextureNormal(SOUND_BUTTON_FILE_NAME);
        _muteButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::muteSounds, this));
    }
}
