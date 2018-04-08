//
//  Car.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "Car.hpp"

Car::Car() {
    
    car.setTexture(IOhandler::getIOhandler().getKartTexture());
    car.setOrigin(45, 110); //rotation center
    
    speedVector.x = 0;
    speedVector.y = 0;
    speed = 0;
    angle = M_PI/2;
    max = 18;
    acceleration = 0.08;
    rolling = 0.01;
    braking = 0.13;
    turnSpeed = 0.043;
    
    lapCompleted = -1;
    disableMove = false;
    atStartLine = false;
    
    updateRotation(); //to set car horizontal
    
}


void Car::roll(void) {
    if (speed - rolling>0) speed -= rolling;
    else if (speed +rolling<0) speed += rolling;
    else speed = 0.0;
}

void Car::updatePosition(void) {
    if (speed>-0.01 && speed<0.01) { // if speed is close to 0
        speed = 0.0;
        return;
    }
    carPosition.x += sin(angle)*speed;
    carPosition.y -= cos(angle)*speed;
    speedVector.x = speed*sin(angle);
    speedVector.y = speed*cos(angle);
    car.setPosition(carPosition);
    updateRotation();
}

void Car::updateRotation(void) {
    car.setRotation(angle*180/M_PI);
    if (angle>2*M_PI) angle -= 2*M_PI;
    else if (angle<0) angle += 2*M_PI;
}

void Car::reset(void) {
    carPosition.x = 5000-300*GameSettings::getGameSettings().opponentsNumber;
    carPosition.y = 7500;
    speedVector.x = 0;
    speedVector.y = 0;
    speed = 0;
    angle = M_PI_2;
    speedVector.x = (speed+acceleration)*sin(angle);
    speedVector.y = (speed+acceleration)*cos(angle);
    speed = sqrt((speedVector.x*speedVector.x)+(speedVector.y*speedVector.y));
    updatePosition(); //to set car horizontal
}

Sprite Car::getSprite(void) const {
    return car;
}


