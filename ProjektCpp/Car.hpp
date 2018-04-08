//
//  Car.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef Car_hpp
#define Car_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "IOhandler.hpp"
#include <cmath>

using namespace sf;

class Car {
public:
    Car();
    
    Sprite car;
    float speed, angle, max, acceleration, rolling, braking, turnSpeed;
    int lapCompleted;
    bool disableMove;
    bool atStartLine;
    Vector2f carPosition, speedVector;
    Sprite getSprite() const;
    
    virtual bool drive() =0;
    
    void roll();
    void updatePosition();
    void updateRotation();
    void reset();

private:
    Texture kartTexture;
};

#endif /* Car_hpp */
