//
//  Opponent.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "Opponent.hpp"

Opponent::Opponent(int i) {
    carPosition.x = 5000 - 300*i;
    carPosition.y = 7500;
    car.setPosition(carPosition);
    actualLap = 0;
    actualCheckpoint = 0;
    acceleration = 0.08;
    turnSpeed = 0.042;
    car.setColor(GameSettings::getGameSettings().opponentColor[i]);
    
    switch (GameSettings::getGameSettings().difficulty) {
        case GameSettings::EASY:
            max = 15;
            break;
            
        case GameSettings::MEDIUM:
            max = 16;
            break;
            
        case GameSettings::HARD:
            max = 17;
            break;
            
        case GameSettings::EXPERT:
            max = 18;
            break;
        
        default:
            break;
    }
}

bool Opponent::drive() {
    int lapNumber = GameSettings::getGameSettings().lapNumber;
    int levelNumber = GameSettings::getGameSettings().levelNumber;
    
    //how many checkpoints
    int levelCheckpoints = static_cast<int>(IOhandler::getIOhandler().getCheckpoints()[levelNumber].size());
    
    if (actualLap < lapNumber) {
        if (actualCheckpoint < levelCheckpoints) {
            
            if (ai.checkpointReached(carPosition,
                                     IOhandler::getIOhandler().getCheckpoints()[levelNumber][actualCheckpoint])) {
                actualCheckpoint++;
            }
            else {
                goToCheckpoint(IOhandler::getIOhandler().getCheckpoints()[levelNumber][actualCheckpoint]);
            }
        }
        else {
            actualLap++;
            actualCheckpoint = 0;
        }
    }
    else {
        roll();
    }
    return true;
}

void Opponent::goToCheckpoint(Vector2i checkpoint) {
    
    float fi = ai.calculateAngle(carPosition, checkpoint);
    float d = 0.1;
    if ((angle>fi+d)||(angle<fi-d)) {
        if (fi<M_PI) {
            if ((angle>fi)&&(angle<(fi+M_PI))) turnLeft();
            else turnRight();
        }
        else if (fi>M_PI) {
            if ((angle<fi)&&(angle>(fi-M_PI))) turnRight();
            else turnLeft();
        }
    }
    accelerate();
    
}

void Opponent::accelerate() {
    if (speed<max) {
        if (speed>=0.0) { //if speed is close to 0
            speedVector.x = (speed+acceleration)*sin(angle);
            speedVector.y = (speed+acceleration)*cos(angle);
            speed = sqrt((speedVector.x*speedVector.x)+(speedVector.y*speedVector.y));
        }
    }
    else roll();
}

void Opponent::turnLeft() {
    if(speed!=0) {
        angle -= turnSpeed;
    }
}

void Opponent::turnRight() {
    if(speed!=0) {
        angle += turnSpeed;
    }
}
