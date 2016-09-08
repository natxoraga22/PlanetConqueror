//
//  SimpleAI.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 15/11/15.
//
//

#ifndef SimpleAI_h
#define SimpleAI_h

#include "cocos2d.h"
#include "Planet.h"
#include "Difficulty.h"

USING_NS_CC;


class SimpleAI : public Node
{
private:
    Vector<Planet*> _planets;
    Difficulty _difficulty;
    
    virtual void computeActionsEasy();
    virtual void computeActionsMedium();
    virtual void computeActionsHard();
    
public:
    // Init code. This function is called from the create() function
    static SimpleAI* create(const Vector<Planet*>& planets, Difficulty difficulty);
    virtual bool init(const Vector<Planet*>& planets, Difficulty difficulty);
 
    virtual void computeActions(float dt);
};


#endif /* SimpleAI_h */
