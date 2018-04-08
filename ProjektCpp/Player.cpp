//
//  Player.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "Player.hpp"

Player::Player(void) {

}

bool Player::drive() {
    
    if(Keyboard::isKeyPressed(Keyboard::Up)) up = 1;
    if(Keyboard::isKeyPressed(Keyboard::Down)) down = 1;
    if(Keyboard::isKeyPressed(Keyboard::Left)) left = 1;
    if(Keyboard::isKeyPressed(Keyboard::Right)) right = 1;
    if(Keyboard::isKeyPressed(Keyboard::Escape)) return false;
    
    if(up==1) accelerate();
    if(down==1) brake();
    if(left==1) turnLeft();
    if(right==1) turnRight();
    if(up==0 && down==0) roll();
    
    return true;
}

void Player::accelerate(void) {
    if (speed<max) {
        if (speed>=0.0) { //if speed is close to 0
            speedVector.x = (speed+acceleration)*sin(angle);
            speedVector.y = (speed+acceleration)*cos(angle);
            speed = sqrt((speedVector.x*speedVector.x)+(speedVector.y*speedVector.y));
        }
        else {
            speedVector.x = (speed+braking)*sin(angle);
            speedVector.y = (speed+braking)*cos(angle);
            speed = -sqrt((speedVector.x*speedVector.x)+(speedVector.y*speedVector.y));
        }
    }
}

void Player::brake(void) {
    if (speed>-max) {
        if (speed>0.0) {
            speedVector.x = (speed-braking)*sin(angle);
            speedVector.y = (speed-braking)*cos(angle);
            speed = sqrt((speedVector.x*speedVector.x)+(speedVector.y*speedVector.y));
            
        }
        else {
            speedVector.x = (speed-acceleration)*sin(angle);
            speedVector.y = (speed-acceleration)*cos(angle);
            speed = -sqrt((speedVector.x*speedVector.x)+(speedVector.y*speedVector.y));
        }
    }
}

void Player::turnLeft(void) {
    if(speed!=0) {
        angle -= (turnSpeed*speed)/max;
    }
}

void Player::turnRight(void) {
    if(speed!=0) {
        angle += (turnSpeed*speed)/max;
    }
}

float Player::getSpeed(void) {
    return speed;
}

