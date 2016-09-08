//
//  Random.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 13/11/15.
//
//

#ifndef Random_h
#define Random_h


class Random
{
public:
    // You must call this method in order to get different randoms each time you run the app
    static void setSeed();
    
    static int getRandomInt(int min, int max);
    static float getRandomFloat(float min, float max);
};


#endif /* Random_h */
