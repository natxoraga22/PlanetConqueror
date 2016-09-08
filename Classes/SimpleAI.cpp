//
//  SimpleAI.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 15/11/15.
//
//

#include "SimpleAI.h"
#include "Random.h"
#include "Constants.h"


#pragma mark - Init

SimpleAI* SimpleAI::create(const Vector<Planet*>& planets, Difficulty difficulty)
{
    SimpleAI *pRet = new SimpleAI();
    if (pRet && pRet->init(planets, difficulty)) pRet->autorelease();
    else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

bool SimpleAI::init(const Vector<Planet*>& planets, Difficulty difficulty)
{
    if (!Node::init()) return false;
    
    _planets = planets;
    _difficulty = difficulty;
    
    this->schedule(schedule_selector(SimpleAI::computeActions), COMPUTE_AI_INTERVAL);

    return true;
}


#pragma mark - AI computing

void SimpleAI::computeActions(float dt)
{
    switch (_difficulty) {
        case Difficulty::Easy: computeActionsEasy(); break;
        case Difficulty::Medium: computeActionsMedium(); break;
        case Difficulty::Hard: computeActionsHard(); break;
        default: break;
    }
}

void SimpleAI::computeActionsEasy()
{
    // Send ships from some CPU planets to random player or neutral planets
    int attackCount = 0;
    for (unsigned int i = 0; i < _planets.size(); i++) {
        auto planet = _planets.at(i);
        if (planet->getOwner() == Player::CPU && Random::getRandomInt(1, 1 + attackCount*3.0) == 1) {
            attackCount++;
            
            int destinationPlanetIndex;
            while (true) {
                destinationPlanetIndex = Random::getRandomInt(0, (int)_planets.size() - 1);
                if (_planets.at(destinationPlanetIndex)->getOwner() != Player::CPU) break;
            }
            planet->attackPlanet(_planets.at(destinationPlanetIndex));
        }
    }
}

void SimpleAI::computeActionsMedium()
{
    // Send ships from some CPU planets to random player or neutral planets
    int attackCount = 0;
    for (unsigned int i = 0; i < _planets.size(); i++) {
        auto planet = _planets.at(i);
        if (planet->getOwner() == Player::CPU && Random::getRandomInt(1, attackCount + 1) == 1) {
            attackCount++;
            
            int destinationPlanetIndex;
            while (true) {
                destinationPlanetIndex = Random::getRandomInt(0, (int)_planets.size() - 1);
                if (_planets.at(destinationPlanetIndex)->getOwner() != Player::CPU) break;
            }
            planet->attackPlanet(_planets.at(destinationPlanetIndex));
        }
    }
}

void SimpleAI::computeActionsHard()
{
    // Send ships from every CPU planet to the closest non-CPU planet
    for (unsigned int i = 0; i < _planets.size(); i++) {
        auto planet = _planets.at(i);
        if (planet->getOwner() == Player::CPU) {

            float minDistance = 9999;
            int minDistancePlanetIndex;
            for (unsigned int j = 0; j < _planets.size(); j++) {
                auto destinationPlanet = _planets.at(j);
                if (destinationPlanet->getOwner() != Player::CPU) {
                    float distance = planet->getPosition().getDistance(destinationPlanet->getPosition());
                    if (distance < minDistance) {
                        minDistance = distance;
                        minDistancePlanetIndex = j;
                    }
                }
            }
            planet->attackPlanet(_planets.at(minDistancePlanetIndex));
        }
    }
}