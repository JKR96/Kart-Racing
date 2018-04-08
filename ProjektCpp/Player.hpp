//
//  Player.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "Car.hpp"

using namespace sf;

class Player : public Car {
public:
    Player(void);
    
    virtual bool drive();
    float getSpeed(void);
    void accelerate();
    void brake();
    void turnLeft();
    void turnRight();
    
    bool up, down, left, right;

};

#endif /* Player_hpp */
