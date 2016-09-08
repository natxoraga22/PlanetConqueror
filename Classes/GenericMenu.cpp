//
//  GenericMenu.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#include "GenericMenu.h"
#include "Resources.h"
#include "Constants.h"


#pragma mark - Init methods

bool GenericMenu::init()
{
    if (!Layer::init()) return false;
    
    _viewOrigin = Director::getInstance()->getVisibleOrigin();
    _viewSize = Director::getInstance()->getVisibleSize();
    
    this->initBackground();
    this->initLogo();
    
    return true;
}

void GenericMenu::initBackground()
{
    auto background = Sprite::create(BACKGROUND_IMAGE_NAME);
    
    Size backgroundSize = background->getContentSize();
    background->setScale(_viewSize.width/backgroundSize.width, _viewSize.height/backgroundSize.height);
    
    background->setAnchorPoint(Vec2(0.0, 0.0));
    background->setPosition(_viewOrigin);
    
    this->addChild(background, -1);
}

void GenericMenu::initLogo()
{
    // Social Point logo
    auto socialPointLogo = Sprite::create(SOCIAL_POINT_LOGO_IMAGE_NAME);
    socialPointLogo->setAnchorPoint(Vec2(1.0, 0.0));
    float positionX = _viewOrigin.x + _viewSize.width - _viewSize.width * MENU_LOGO_OFFSET_RATIO;
    float positionY = _viewOrigin.y + _viewSize.height * MENU_LOGO_OFFSET_RATIO;
    socialPointLogo->setPosition(positionX, positionY);
    socialPointLogo->setScale(_viewSize.width * MENU_LOGO_SIZE_RATIO / socialPointLogo->getBoundingBox().size.width);
    this->addChild(socialPointLogo);
}