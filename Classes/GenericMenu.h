//
//  GenericMenu.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#ifndef GenericMenu_h
#define GenericMenu_h


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;


class GenericMenu : public Layer
{
private:
    // Init auxiliar methods
    virtual void initBackground();
    virtual void initLogo();

protected:
    Vec2 _viewOrigin;
    Size _viewSize;
    
public:
    // Init code. This function is called from the create() function
    virtual bool init();
    
    // implement the "static create()" method
    CREATE_FUNC(GenericMenu);
};


#endif /* GenericMenu_h */
