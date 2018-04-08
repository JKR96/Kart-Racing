//
//  AI.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 17.12.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "AI.hpp"

float AI::calculateAngle(Vector2f carPosition, Vector2i checkpoint) const {
    float angle;
    angle = atan2(checkpoint.x-carPosition.x, -checkpoint.y+carPosition.y);
    if (angle>2*M_PI) angle -= 2*M_PI;
    else if (angle<0) angle += 2*M_PI;
    return angle;
}

bool AI::checkpointReached(Vector2f carPosition, Vector2i checkpoint) const {
    float xDiff, yDiff, d;
    xDiff = checkpoint.x - carPosition.x;
    yDiff = checkpoint.y - carPosition.y;
    d = sqrt((xDiff*xDiff)+(yDiff*yDiff));
    if (d<DISTANCE) return true;
    else return false;
}


