//
//  GameSettings.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef GameSettings_hpp
#define GameSettings_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "IOhandler.hpp"
#include <chrono>

using namespace sf;

//singleton
class GameSettings { 
public:
    static GameSettings & getGameSettings()
    {
        static GameSettings gameSettings;
        return gameSettings;
    }
    /////////////////////////////////////
    
    RenderWindow window;
    int allLevels;
    int levelNumber;
    int lapNumber;
    int opponentsNumber;
    void setAllLevels(int levels);
    Vector2f& getResolution();
    std::vector <Color> opponentColor;
    enum DifficultyLevel {EASY, MEDIUM, HARD, EXPERT};
    DifficultyLevel difficulty;
    
private:
    GameSettings(void);
    GameSettings(const GameSettings &);
    /////////////////////////////////////
    
    Vector2f resolution;
};

#endif /* GameSettings_hpp */
