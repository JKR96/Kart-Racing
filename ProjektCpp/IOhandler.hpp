//
//  IOhandler.hpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#ifndef IOhandler_hpp
#define IOhandler_hpp

#pragma once
#include <SFML/Graphics.hpp>
#include "LevelMap.hpp"
#include "GameSettings.hpp"
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace sf;

//singleton
class IOhandler {
public:
    static IOhandler & getIOhandler()
    {
        static IOhandler handler;
        return handler;
    }
    //////////////////////////////////////////////
    
    Texture& getKartTexture();
    Texture& getMenu1();
    Texture& getMenu2();
    Texture& getAsphalt();
    Texture& getCurb();
    Font& getFont1();
    Font& getFont2();
    float getLapRecord();
    std::vector <int> getSpriteTab();
    std::vector < std::vector <Vector3i> > getSpritePositions();
    std::vector < std::vector <Vector2i> > getCheckpoints();
    
    int allLevels;
    std::vector <int> spriteTab;
    float lapRecordMinutes;
    float lapRecordSeconds;
    static std::string configFile;
    static std::string recordFile;
    static std::string checkpointFile;
    
private:
    IOhandler();
    IOhandler(const IOhandler &);
    ////////////////////////////////////////////
    
    bool readConfigFile();
    bool readRecordFile();
    bool readCheckpointFile();
    float readLapRecordMinutes(std::fstream &data);
    float readLapRecordSeconds(std::fstream &data);
    int readLevelNumber(std::fstream &data);
    void readLevelSprites(std::fstream &data);
    void readSpritePositions(std::fstream &data);
    void readCheckpoints(std::fstream &data);
    void saveLapRecord(std::fstream &data);
    Texture kartTexture, menu1, menu2, curb, asphalt;
    Font font1, font2;
    std::vector < std::vector <Vector3i> > spritePositions; //data about sprites
    std::vector <int> levelCheckpoints; //how many checkpoints in level
    std::vector < std::vector <Vector2i> > checkPoints; //checkpoints' coordinates
    
};


#endif /* IOhandler_hpp */
