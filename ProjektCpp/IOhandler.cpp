//
//  IOhandler.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "IOhandler.hpp"

std::string IOhandler::configFile = "/Users/Kuba/Documents/programy/c++/ProjektCpp/Config/data";
std::string IOhandler::recordFile = "/Users/Kuba/Documents/programy/c++/ProjektCpp/Config/record";
std::string IOhandler::checkpointFile = "/Users/Kuba/Documents/programy/c++/ProjektCpp/Config/checkpoints";


IOhandler::IOhandler(void) {
    //reading from files
    if (!kartTexture.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/images/car.png")) {
        exit(1);
    }
    if (!menu1.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/images/s1.jpg")) {
        exit(1);
    }
    if (!menu2.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/images/s2.jpg")) {
        exit(1);
    }
    if (!asphalt.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/images/asphalt.jpg")) {
        exit(1);
    }
    if (!font1.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/fonts/indiana.ttf")) {
        exit(1);
    }
    if (!font2.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/fonts/future.ttf")) {
        exit(1);
    }
    if (!curb.loadFromFile("/Users/Kuba/documents/programy/c++/projektcpp/images/curb.jpg")) {
        exit(1);
    }
    //read config
    if (!readConfigFile()) {
        //error
        std::cerr << "Unable to open config file" << std::endl;
        exit(1);
    }
    if (!readRecordFile()) {
        //error
        std::cerr << "Unable to open record file" << std::endl;
        exit(1);
    }
    if (!readCheckpointFile()) {
        //error
        std::cerr << "Unable to open record file" << std::endl;
        exit(1);
    }
}

bool IOhandler::readConfigFile(void) {
    std::fstream data;
    data.open(configFile, std::ios::in);
    if (data.good()==false) {
        return false;
    }
    
    allLevels = readLevelNumber(data);
    readLevelSprites(data);
    readSpritePositions(data);
    
    data.close();
    return true;
}

bool IOhandler::readRecordFile(void) {
    std::fstream data;
    data.open(recordFile, std::ios::in);
    if (data.good()==false) {
        return false;
    }
    
    lapRecordMinutes = readLapRecordMinutes(data);
    lapRecordSeconds = readLapRecordSeconds(data);

    data.close();
    return true;
}

bool IOhandler::readCheckpointFile() {
    std::fstream data;
    data.open(checkpointFile, std::ios::in);
    if (data.good()==false) {
        return false;
    }
    
    readCheckpoints(data);
    
    data.close();
    return true;
}

float IOhandler::readLapRecordMinutes(std::fstream &data) {
    std::string temp;
    getline(data, temp);
    lapRecordMinutes = std::stof(temp);
    return lapRecordMinutes;
}

float IOhandler::readLapRecordSeconds(std::fstream &data) {
    std::string temp;
    getline(data, temp);
    lapRecordSeconds = stof(temp);
    return lapRecordSeconds;
}

int IOhandler::readLevelNumber(std::fstream &data) {
    std::string temp;
    getline(data, temp);
    int allLevels = stoi(temp);
    return allLevels;
}

void IOhandler::readLevelSprites(std::fstream &data) {
    std::string temp;
    for (int i=0; i<allLevels; i++) {
        getline(data, temp);
        spriteTab.push_back(stoi(temp));
    }
}

void IOhandler::readSpritePositions(std::fstream &data) {
    //how many sprites
    std::string str = "";
    for (int i=0; i<allLevels; i++) {
        spritePositions.push_back(std::vector<Vector3i>());
    }
    //read data
    for (int i=0; i<allLevels; i++) {
        for (int j=0; j<spriteTab[i]; j++) {
            Vector3i tempVector;
            getline(data, str);
            tempVector.x = stoi(str);
            getline(data, str);
            tempVector.y = stoi(str);
            getline(data, str);
            tempVector.z = stoi(str);
            spritePositions[i].push_back(tempVector);
        }
    }
}

void IOhandler::readCheckpoints(std::fstream &data) {
    //how many sprites
    std::string str = "";
    for (int i=0; i<allLevels; i++) {
        getline(data, str);
        levelCheckpoints.push_back(stoi(str));
    }
    //read checkpoints
    for (int i=0; i<allLevels; i++) {
        checkPoints.push_back(std::vector<Vector2i>()); //2nd dimension
        for (int j=0; j<levelCheckpoints[i]; j++) {
            Vector2i tempVector;
            getline(data, str);
            tempVector.x = stoi(str);
            getline(data, str);
            tempVector.y = stoi(str);
            checkPoints[i].push_back(tempVector);
        }
    }
}

Texture& IOhandler::getKartTexture(void) {
    return kartTexture;
}

Texture& IOhandler::getMenu1(void) {
    return menu1;
}

Texture& IOhandler::getMenu2(void) {
    return menu2;
}

Texture& IOhandler::getAsphalt(void) {
    return asphalt;
}

Texture& IOhandler::getCurb(void) {
    return curb;
}

Font& IOhandler::getFont1(void) {
    return font1;
}

Font& IOhandler::getFont2(void) {
    return font2;
}

std::vector <int> IOhandler::getSpriteTab(void) {
    return spriteTab;
}

std::vector < std::vector <Vector3i> > IOhandler::getSpritePositions(void) {
    return spritePositions;
}

std::vector < std::vector <Vector2i> > IOhandler::getCheckpoints() {
    return checkPoints;
}

