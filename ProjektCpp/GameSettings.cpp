//
//  GameSettings.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "GameSettings.hpp"

GameSettings::GameSettings(void) {
    
    //window settings
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    //ContextSettings settings;
    //settings.antialiasingLevel = 10;
    window.create(VideoMode(resolution.x-50,resolution.y-50), "");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(150);
    
    //loading screen
    Text loading;
    Font tempFont;
    if (!tempFont.loadFromFile("indiana.ttf")) {
        std::cout << "Unable to load font!\n";
        exit(1);
    }
    loading.setFont(tempFont);
    loading.setCharacterSize(150);
    loading.setString("Loading");
    loading.setPosition((resolution.x/2)-(loading.getGlobalBounds().width/2), resolution.y/2.4);
    loading.setFillColor(Color::Red);
    window.clear(Color::Black);
    window.draw(loading);
    window.display();
    
    //race settings
    opponentsNumber = 3;
    lapNumber = 1;
    levelNumber = 0;
    
    //opponents colors
    opponentColor.push_back(Color::Red);
    opponentColor.push_back(Color::Green);
    opponentColor.push_back(Color::Yellow);
    opponentColor.push_back(Color::Blue);
    opponentColor.push_back(Color::Magenta);
    opponentColor.push_back(Color::Cyan);
    opponentColor.push_back(Color(255, 140, 0)); //orange
    
    //difficulty
    difficulty = MEDIUM;
    
    //create IOhandler
    IOhandler::getIOhandler();

}

void GameSettings::setAllLevels(int levels) {
    allLevels = levels;
}

Vector2f& GameSettings::getResolution() {
    return resolution;
}
