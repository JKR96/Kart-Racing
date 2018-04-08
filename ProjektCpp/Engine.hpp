//
//  Engine.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "LevelMap.hpp"
#include "GameSettings.hpp"
#include "Opponent.hpp"
#include "Timer.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <memory>

using namespace sf;
using namespace std;

#define RESOLUTION GameSettings::getGameSettings().getResolution()
#define WINDOW GameSettings::getGameSettings().window

class Engine {
public:
    Engine();
    
    void runEngineTT(int levelNumber);
    void runEngineRACE(int levelNumber);
  
private:
    
    Player myPlayer;
    Vector2f viewCenter;
    Vector2f viewSize;
    View view;
    Sprite background;
    vector <string> result;
    Timer timer;
    int opponentsReachedFinish;
    
    void setGameView();
    string processAllCollisions(LevelMap& level, int levelNumber, Timer& timer); //TT
    bool processAllCollisions(LevelMap& level, vector <Opponent>& opponents, int levelNumber, Timer& timer);//RACE
    void processCurbCollisions(LevelMap& level, int levelNumber);
    string processStartLine(LevelMap& level, Timer& timer); //TT
    bool processStartLine(LevelMap& level, Opponent opponent); //RACE - opponents
    bool processStartLine(LevelMap& level); //RACE - player
    void processCarCollisions(vector <Opponent>& opponents);
    void resetTT();
    void resetRACE();
    void showResults();
};

#endif /* Engine_hpp */
