//
//  Planet.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#include "Planet.h"
#include "Resources.h"
#include "Constants.h"
#include "Random.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


#pragma mark - Init

Planet* Planet::create(Player player)
{
    Planet *pRet = new Planet();
    if (pRet && pRet->init(player)) pRet->autorelease();
    else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

bool Planet::init(Player player)
{
    _owner = player;
    _selected = false;
    
    if (!Sprite::initWithFile(this->planetFileForPlayer(_owner, _selected))) return false;
 
    // Touch event listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Planet::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Planet::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Planet::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(Planet::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _userInteractionEnabled = true;
    
    // Ship counter
    _shipCounter = Label::createWithTTF("0", FONT_FILE_NAME, PLANET_SHIP_COUNTER_FONT_SIZE);
    _shipCounter->setAlignment(TextHAlignment::CENTER);
    _shipCounter->setPosition(this->getBoundingBox().size.width/2.0, this->getBoundingBox().size.height/2.0);
    this->addChild(_shipCounter);
    
    _maxNumberOfShips = Random::getRandomInt(MIN_MAX_SHIPS_PER_PLANET, MAX_MAX_SHIPS_PER_PLANET);
    
    this->schedule(schedule_selector(Planet::incrementShips), INCREMENT_SHIPS_INTERVAL);
    
    return true;
}

string Planet::planetFileForPlayer(Player player, bool selected)
{
    switch (player) {
        case Player::None:
            return GREY_PLANET_IMAGE_NAME;
        case Player::Human:
            if (selected) return SELECTED_GREEN_PLANET_IMAGE_NAME;
            else return GREEN_PLANET_IMAGE_NAME;
        case Player::CPU:
            return RED_PLANET_IMAGE_NAME;
        default:
            return "";
    }
}

string Planet::shipFileForPlayer(Player player)
{
    switch (player) {
        case Player::None: return "";
        case Player::Human: return HUMAN_PLAYER_SHIP_IMAGE_NAME;
        case Player::CPU: return CPU_PLAYER_SHIP_IMAGE_NAME;
        default: return "";
    }
}


#pragma mark - Getters & Setters

bool Planet::isSelected()
{
    return _selected;
}

Player Planet::getOwner()
{
    return _owner;
}

void Planet::setDelegate(PlanetDelegate *delegate)
{
    _delegate = delegate;
}

void Planet::setOwner(Player player)
{
    if (_owner != player) {
        _owner = player;
        this->setTexture(this->planetFileForPlayer(_owner, _selected));
    }
}

void Planet::setSelected(bool selected)
{
    if (_selected != selected) {
        _selected = selected;
        this->setTexture(this->planetFileForPlayer(_owner, _selected));
    }
}

void Planet::setNumberOfShips(int numberOfShips)
{
    if (_numberOfShips != numberOfShips) {
        _numberOfShips = numberOfShips;
        _shipCounter->setString(to_string(_numberOfShips));
    }
}


#pragma mark - Actions

void Planet::incrementShips(float dt)
{
    if (_owner != Player::None && _numberOfShips < _maxNumberOfShips) {
        this->setNumberOfShips(_numberOfShips + 1);
    }
}

void Planet::attackPlanet(Planet* planet)
{
    Size viewSize = Director::getInstance()->getVisibleSize();

    for (int i = 0; i < _numberOfShips; i++) {
        // Creating the ship
        auto ship = Sprite::create(this->shipFileForPlayer(_owner));
        Size planetSize = this->getContentSize();
        Size shipSize = ship->getContentSize();
        int positionX = Random::getRandomInt(0.0, planetSize.width);
        int positionY = Random::getRandomInt(0.0, planetSize.height);
        ship->setPosition(positionX, positionY);
        ship->setScale(viewSize.width * (_owner == Player::Human ? PLAYER_SHIP_SIZE_RATIO : CPU_SHIP_SIZE_RATIO) / shipSize.width);
        if (this->getPosition().x > planet->getPosition().x) ship->setFlippedX(true);
        
        this->addChild(ship);
        ship->setGlobalZOrder(1);
        
        // Moving the ship to the destination planet
        auto distance = this->getPosition().distance(planet->getPosition());
        float duration = distance / Random::getRandomFloat(MIN_SHIP_SPEED, MAX_SHIP_SPEED);
        
        auto moveAction = MoveTo::create(duration, Sprite::convertToNodeSpace(planet->getPosition()));
        auto callback = CallFunc::create(CC_CALLBACK_0(Planet::underAttack, planet, _owner));
        auto removeAction = RemoveSelf::create();
        auto sequence = Sequence::create(moveAction, callback, removeAction, nullptr);
        ship->runAction(sequence);
    }
    this->setNumberOfShips(0);
    this->setSelected(false);
}

void Planet::underAttack(Player attackingPlayer)
{
    if (attackingPlayer == _owner) {
        this->setNumberOfShips(_numberOfShips + 1);
    }
    else {
        if (_numberOfShips == 0) {
            this->setOwner(attackingPlayer);
            this->setSelected(false);
            this->setNumberOfShips(1);
            
            // Sound
            if (!UserDefault::getInstance()->getBoolForKey(MUTE_KEY, false)) {
                SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_SFX);
            }
            
            // Particles
            ParticleSystemQuad* explosion;
            if (attackingPlayer == Player::Human) explosion = ParticleSystemQuad::create(GREEN_PLANET_EXPLOSION);
            if (attackingPlayer == Player::CPU) explosion = ParticleSystemQuad::create(RED_PLANET_EXPLOSION);
            explosion->setPosition(this->getBoundingBox().size.width/2.0, this->getBoundingBox().size.height/2.0);
            this->addChild(explosion);
            
            _delegate->planetOwnerChanged(this);
        }
        else this->setNumberOfShips(_numberOfShips - 1);
    }
}


#pragma mark - Touch handling

void Planet::enableUserInteraction()
{
    _userInteractionEnabled = true;
}

void Planet::disableUserInteraction()
{
    _userInteractionEnabled = false;
}

bool Planet::onTouchBegan(Touch *touch, Event *event)
{
    if (_userInteractionEnabled && this->touchInsidePlanet(touch)) {
        if (_owner == Player::Human) {
            this->setSelected(!_selected);
        }
        else if (_owner == Player::CPU || _owner == Player::None) {
            _delegate->attackablePlanetClicked(this);
        }
    }
    return true;
}

void Planet::onTouchMoved(Touch *touch, Event *event) {}

void Planet::onTouchEnded(Touch *touch, Event *event) {}

void Planet::onTouchCancelled(Touch *touch, Event *event) {}

bool Planet::touchInsidePlanet(Touch *touch)
{
    auto boundingBox = this->getBoundingBox();
    auto center = boundingBox.origin + boundingBox.size/2.0;
    auto radius = boundingBox.size.width/2.0;
    
    return center.distance(touch->getLocation()) <= radius;
}
