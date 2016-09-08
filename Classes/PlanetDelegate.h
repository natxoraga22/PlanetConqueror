//
//  PlanetDelegate.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 14/11/15.
//
//

#ifndef PlanetDelegate_h
#define PlanetDelegate_h


class Planet;


class PlanetDelegate
{
public:
    virtual void attackablePlanetClicked(Planet *planet) = 0;
    virtual void planetOwnerChanged(Planet *planet) = 0;
};


#endif /* PlanetDelegate_h */
