//
//  Timer.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "Timer.hpp"

Timer::Timer(void) {
    seconds = 0.0;
    minutes = 0;
}


void Timer::start(void) {
    clock.restart();
    fiveSecondClock.restart();
}

std::string Timer::stop(void) {
    if ( (minutes>0) || ((minutes==0)&&(seconds>15)) ) {
        time = clock.getElapsedTime();
        seconds = time.asSeconds();
        if (chceckRecord()==true) {
            if (saveRecord()==false) {
                std::cerr << "Unable to save record in record file!\n";
                exit(1);
            }
        }
        if (seconds>=60.0) {
            minutes += 1;
            time = clock.restart();
            timeString.resize(12);
        }
        else {
            timeString.resize(11);
        }
        std::string timeString = "Lap:" + std::to_string(minutes) + ":" + std::to_string(seconds);
        previousLap = timeString;
        minutes = 0;
        seconds = 0.0;
        return timeString;
    }
    else {
        return previousLap;
    }
}

std::string Timer::showTime(void) {
    time = clock.getElapsedTime();
    seconds = time.asSeconds();
    if (seconds>=60.0) {
        minutes += 1;
        time = clock.restart();
    }
    std::string timeString = "Lap:" + std::to_string(minutes) + ":" + std::to_string(seconds);
    if (seconds>10) timeString.resize(11);
    else timeString.resize(10);
    return timeString;
}

bool Timer::chceckRecord(void) {
    float sec = minutes*60 + seconds;
    if (sec<IOhandler::getIOhandler().lapRecordMinutes*60 + IOhandler::getIOhandler().lapRecordSeconds) {
        return true;
    }
    return false;
}

bool Timer::is5Seconds(void) {
    if ((seconds<5.0) && (minutes==0)) {
        return true;
    }
    return false;
}

std::string Timer::getPreviousLap(void) {
    return previousLap;
}

bool Timer::saveRecord() { 
    //open file
    std::fstream data;
    data.open(IOhandler::recordFile, std::ios::out);
    if (data.good()==false) {
        std::cerr << "Unable to open data file!\n";
        return false;
    }
    
    //write record
    data << minutes << std::endl;
    data << seconds;
    
    //close file
    data.close();
    return true;
}

void Timer::reset() {
    clock.restart();
    fiveSecondClock.restart();
    minutes = 0;
    seconds = 0.0;
}


