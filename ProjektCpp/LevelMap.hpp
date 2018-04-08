//
//  LevelMap.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef LevelMap_hpp
#define LevelMap_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.hpp"
#include "IOhandler.hpp"
#include <vector>

#define WINDOW GameSettings::getGameSettings().window
#define LEVELS GameSettings::getGameSettings().allLevels

using namespace sf;

class LevelMap {
public:
    LevelMap(int levelNumber);
    
    void setMap();
    std::vector < std::vector <Sprite> > spriteMaps;
    Sprite startLine;
    
};


#endif /* LevelMap_hpp */
