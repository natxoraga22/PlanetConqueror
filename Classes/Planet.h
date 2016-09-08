//
//  Planet.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#ifndef Planet_h
#define Planet_h


#include "cocos2d.h"
#include "PlanetDelegate.h"

USING_NS_CC;
using namespace std;


enum class Player {
    None = 0,
    Human = 1,
    CPU = 2
};


class Planet : public Sprite
{
private:
    Player _owner;
    PlanetDelegate* _delegate;
    int _numberOfShips;
    int _maxNumberOfShips;
    bool _selected;
    Label* _shipCounter;
    bool _userInteractionEnabled;
    
    // Utility
    virtual string planetFileForPlayer(Player player, bool selected);
    virtual string shipFileForPlayer(Player player);
    
    // Getters & Setters
    virtual void setOwner(Player player);
    virtual void setSelected(bool selected);
    virtual void setNumberOfShips(int numberOfShips);
    virtual void incrementShips(float dt);
    
    // Actions
    virtual void underAttack(Player attackingPlayer);
    
    // Touch Handling
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    virtual bool touchInsidePlanet(Touch *touch);
    
public:
    // Create planet
    static Planet* create(Player player);
    virtual bool init(Player player);
    
    // Getters & Setters
    virtual bool isSelected();
    virtual Player getOwner();
    virtual void setDelegate(PlanetDelegate* delegate);
    
    // User interaction
    virtual void enableUserInteraction();
    virtual void disableUserInteraction();
    
    // Actions
    virtual void attackPlanet(Planet* planet);
};


#endif /* Planet_h */
