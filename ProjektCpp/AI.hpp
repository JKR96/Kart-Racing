//
//  AI.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 17.12.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#define DISTANCE 140

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class AI {
public:
    float calculateAngle(Vector2f carPosition, Vector2i checkpoint) const; 
    bool checkpointReached(Vector2f carPosition, Vector2i checkpoint) const;
};

#endif /* AI_hpp */
