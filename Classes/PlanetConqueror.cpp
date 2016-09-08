//
//  PlanetConqueror.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 13/11/15.
//
//

#include "PlanetConqueror.h"
#include "Resources.h"
#include "Constants.h"
#include "Random.h"
#include "EndGameMenu.h"
#include "SimpleAI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


#pragma mark - Init

Scene* PlanetConqueror::createGameScene(Difficulty difficulty)
{
    auto gameScene = Scene::create();
    
    // this will call the "init" method inside this class
    auto gameLayer = PlanetConqueror::create(difficulty);
    
    gameScene->addChild(gameLayer);
    return gameScene;
}

PlanetConqueror* PlanetConqueror::create(Difficulty difficulty)
{
    PlanetConqueror *pRet = new PlanetConqueror();
    if (pRet && pRet->init(difficulty)) pRet->autorelease();
    else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

bool PlanetConqueror::init(Difficulty difficulty)
{
    if (!Layer::init()) return false;
    
    _viewOrigin = Director::getInstance()->getVisibleOrigin();
    _viewSize = Director::getInstance()->getVisibleSize();
    _difficulty = difficulty;
    
    Random::setSeed();
    
    this->initBackground();
    this->initPauseButton();
    this->initPlanets();
    
    // AI
    _ai = SimpleAI::create(_planets, _difficulty);
    this->addChild(_ai);
    
    // Music
    if (!UserDefault::getInstance()->getBoolForKey(MUTE_KEY, false)) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_BACKGROUND_MUSIC, true);
    }
    return true;
}

void PlanetConqueror::initBackground()
{
    auto background = Sprite::create(BACKGROUND_IMAGE_NAME);
    
    // Size
    Size backgroundSize = background->getContentSize();
    background->setScale(_viewSize.width/backgroundSize.width, _viewSize.height/backgroundSize.height);
    
    // Anchor point and position
    background->setAnchorPoint(Vec2(0.0, 0.0));
    background->setPosition(_viewOrigin);
    
    this->addChild(background, -1);
}

void PlanetConqueror::initPauseButton()
{
    _pauseButton = Button::create(PAUSE_BUTTON_FILE_NAME, "", "");
    _pauseButton->setAnchorPoint(Vec2(1.0, 1.0));
    float positionX = _viewOrigin.x + _viewSize.width - _viewSize.width * PAUSE_BUTTON_OFFSET_RATIO;
    float positionY = _viewOrigin.y + _viewSize.height - _viewSize.width * PAUSE_BUTTON_OFFSET_RATIO;
    _pauseButton->setPosition(Vec2(positionX, positionY));
    _pauseButton->setScale(_viewSize.width * PAUSE_BUTTON_SIZE_RATIO / _pauseButton->getBoundingBox().size.width);
    _pauseButton->addTouchEventListener(CC_CALLBACK_2(PlanetConqueror::pauseGame, this));
    this->addChild(_pauseButton);
}

void PlanetConqueror::initPlanets()
{
    // Number of planets
    int numberOfPlanets = Random::getRandomInt(MIN_NUMBER_OF_PLANETS, MAX_NUMBER_OF_PLANETS);

    // Planet layout
    bool layoutValid = false;
    do {
        layoutValid = this->createPlanetLayout(numberOfPlanets);
    } while (!layoutValid);
}

bool PlanetConqueror::createPlanetLayout(int numberOfPlanets)
{
    // Starting planet indexes
    int humanPlanetIndex = Random::getRandomInt(0, numberOfPlanets - 1);
    int cpuPlanetIndex = -1;
    do {
        cpuPlanetIndex = Random::getRandomInt(0, numberOfPlanets - 1);
    }
    while (cpuPlanetIndex == humanPlanetIndex);
    
    // Create the planets without position nor size
    _planets = Vector<Planet*>(numberOfPlanets);
    for (int i = 0; i < numberOfPlanets; i++) {
        Planet* planet;
        if (i == humanPlanetIndex) planet = Planet::create(Player::Human);
        else if (i == cpuPlanetIndex) planet = Planet::create(Player::CPU);
        else planet = Planet::create(Player::None);
        planet->setDelegate(this);
        planet->setVisible(false);  // Used to tag planets not initialized
        
        _planets.insert(i, planet);
    }
    
    // Position every planet in a valid position
    unsigned int i = 0;
    int errorCount = 0;
    while (i < numberOfPlanets) {
        // Planet size
        float sizeRatio = Random::getRandomFloat(PLANET_MIN_SIZE_RATIO, PLANET_MAX_SIZE_RATIO);
        float wantedSize = _viewSize.width * sizeRatio;
        
        // Planet position
        int minPositionX = _viewOrigin.x + wantedSize;
        int maxPositionX = _viewOrigin.x + _viewSize.width - wantedSize;
        int minPositionY = _viewOrigin.y + wantedSize;
        int maxPositionY = _viewOrigin.y + _viewSize.height - wantedSize;
        int positionX = Random::getRandomInt(minPositionX, maxPositionX);
        int positionY = Random::getRandomInt(minPositionY, maxPositionY);
        
        // Planet position and scale
        Planet* planet = _planets.at(i);
        planet->setPosition(positionX, positionY);
        planet->setScale(wantedSize / planet->getContentSize().width);
        
        // Test if the planet is in valid position
        if (planetPositionIsValid(planet)) {
            i++;
            errorCount = 0;
            planet->setVisible(true);
        }
        else {
            errorCount++;
            if (PLANET_LAYOUT_MAX_ERRORS >= 0 && errorCount >= PLANET_LAYOUT_MAX_ERRORS) return false;
        }
    }
    
    // Add the planets to the scene
    for (unsigned int i = 0; i < _planets.size(); i++) this->addChild(_planets.at(i));
    
    return true;
}

bool PlanetConqueror::planetPositionIsValid(Planet* planet)
{
    if (_pauseButton->getBoundingBox().intersectsRect(planet->getBoundingBox())) return false;
 
    bool valid = true;
    for (unsigned int i = 0; i < _planets.size() && valid; i++) {
        auto otherPlanet = _planets.at(i);
        if (otherPlanet->isVisible()) {
            float distance = planet->getPosition().distance(otherPlanet->getPosition());
            distance -= planet->getBoundingBox().size.width/2.0;
            distance -= otherPlanet->getBoundingBox().size.width/2.0;
            
            if (distance < _viewSize.width * MIN_DISTANCE_BETWEEN_PLANETS_RATIO) valid = false;
        }
    }
    return valid;
}


#pragma mark - Pause and resume

void PlanetConqueror::pauseGame(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _pauseButton->loadTextureNormal(RESUME_BUTTON_FILE_NAME);
        _pauseButton->addTouchEventListener(CC_CALLBACK_2(PlanetConqueror::resumeGame, this));
        
        // Disable user interaction
        for (unsigned int i = 0; i < _planets.size(); i++) _planets.at(i)->disableUserInteraction();
        
        Director::getInstance()->pause();
    }
}

void PlanetConqueror::resumeGame(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _pauseButton->loadTextureNormal(PAUSE_BUTTON_FILE_NAME);
        _pauseButton->addTouchEventListener(CC_CALLBACK_2(PlanetConqueror::pauseGame, this));
        
        // Enable user interaction
        for (unsigned int i = 0; i < _planets.size(); i++) _planets.at(i)->enableUserInteraction();
        
        Director::getInstance()->resume();
    }
}


#pragma mark - PlanetDelegate methods

void PlanetConqueror::attackablePlanetClicked(Planet *planet)
{
    for (unsigned int i = 0; i < _planets.size(); i++) {
        auto attackingPlanet = _planets.at(i);
        if (_planets.at(i)->isSelected()) {
            attackingPlanet->attackPlanet(planet);
        }
    }
}

void PlanetConqueror::planetOwnerChanged(Planet *planet)
{
    int humanPlanetsCount = 0;
    int cpuPlanetsCount = 0;
    for (unsigned int i = 0; i < _planets.size(); i++) {
        if (_planets.at(i)->getOwner() == Player::Human) humanPlanetsCount++;
        else if (_planets.at(i)->getOwner() == Player::CPU) cpuPlanetsCount++;
    }
    
    // End game conditions
    if (humanPlanetsCount == 0)
        Director::getInstance()->replaceScene(EndGameMenu::createEndGameMenuScene(MenuType::GameOver, _difficulty));
    else if (cpuPlanetsCount == 0)
        Director::getInstance()->replaceScene(EndGameMenu::createEndGameMenuScene(MenuType::Win, _difficulty));
}
