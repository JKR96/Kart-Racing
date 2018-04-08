//
//  Opponent.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef Opponent_hpp
#define Opponent_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "Car.hpp"
#include "AI.hpp"
#include "IOhandler.hpp"

using namespace sf;

class Opponent : public Car {
public:
    Opponent();
    Opponent(int i);
    
    AI ai;
    
    virtual bool drive();
    
private:
    
    void accelerate();
    void turnLeft();
    void turnRight();
    void goToCheckpoint(Vector2i checkpoint);
    int actualLap;
    int actualCheckpoint;

};

#endif /* Opponent_hpp */
