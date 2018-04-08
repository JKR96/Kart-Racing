//
//  LevelMap.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "LevelMap.hpp"

LevelMap::LevelMap(int levelNumber) {
    // setting vector
    for (int i=0; i<LEVELS; i++) {
        spriteMaps.push_back(std::vector<Sprite>()); //2nd dimension
        for (int j=0; j<IOhandler::getIOhandler().getSpriteTab()[i]; j++) {
            Sprite sprite;
            spriteMaps[i].push_back(sprite);
        }
    }
}

void LevelMap::setMap(void) {
    //loading curbs
    for (int i=0; i<LEVELS; i++) {
        for (int j=0; j<IOhandler::getIOhandler().spriteTab[i]; j++) {
            //set coordinates
            spriteMaps[i][j].setTexture(IOhandler::getIOhandler().getCurb());  //texture 500 x 100 px
            spriteMaps[i][j].setPosition(IOhandler::getIOhandler().getSpritePositions()[i][j].x,                    IOhandler::getIOhandler().getSpritePositions()[i][j].y);
            //set angle
            spriteMaps[i][j].setRotation(IOhandler::getIOhandler().getSpritePositions()[i][j].z);
        }
    }
    //start line
    Texture texture;
    texture.create(50, 720);
    startLine.setTexture(texture);
    startLine.setColor(Color::White);
    startLine.setPosition(5500, 7190);
}

