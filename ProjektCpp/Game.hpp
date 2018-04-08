//
//  Game.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Player.hpp"
#include "Opponent.hpp"
#include "LevelMap.hpp"
#include "IOhandler.hpp"
#include "GameSettings.hpp"
#include "Timer.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#define RESOLUTION GameSettings::getGameSettings().getResolution()
#define WINDOW GameSettings::getGameSettings().window

using namespace sf;

class Game {
public:
    Game(void);
    ~Game(void);
    
    void runGame(); 
    
private:
    enum GameState {MENU, TT, RACE, SETTINGS, ABOUT, END};
    GameState state;
    Engine gameEngine;
    Clock clock;
    enum MenuState {S1, S2, S3, S4, S5};
    MenuState menuState;
    GameState displayMenu(MenuState);
    MenuState increment(MenuState menuState);
    MenuState decrement(MenuState menuState);
    GameState setGameState(MenuState menuState);
    GameSettings::DifficultyLevel increment(GameSettings::DifficultyLevel difficulty);
    GameSettings::DifficultyLevel decrement(GameSettings::DifficultyLevel difficulty);
    void firstScreen();
    void timeTrial();
    void race();
    void about();
    void settings();
};

#endif /* Game_hpp */
