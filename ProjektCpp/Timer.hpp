//
//  Timer.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "IOhandler.hpp"
#include "GameSettings.hpp"
#include <string>

using namespace sf;

class Timer {
public:
    Timer();
    std::string timeString;
    void start();
    std::string stop(); //returns lap time
    std::string showTime();
    bool is5Seconds();
    std::string getPreviousLap();
    void reset();
    Time time;
    
private:
    Clock clock;
    Clock fiveSecondClock;
    int minutes;
    float seconds;
    std::string previousLap;
    bool chceckRecord();
    bool saveRecord();
    
};

#endif /* Timer_hpp */
