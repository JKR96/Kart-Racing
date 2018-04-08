//
//  Engine.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "Engine.hpp"

Engine::Engine() {
    
    //setting view
    viewCenter.x = myPlayer.carPosition.x;
    viewCenter.y = myPlayer.carPosition.y;
    viewSize = RESOLUTION;
    view.setCenter(viewCenter);
    view.setSize(viewSize);
    
    //loading background
    background.setTexture(IOhandler::getIOhandler().getAsphalt());
    background.setPosition(0, 0);
    
    opponentsReachedFinish = 0;
}

void Engine::runEngineTT(int levelNumber) {
    
    resetTT();
    
    //level
    LevelMap level(levelNumber);
    level.setMap();
    
    //timer
    Text timeText;
    string timeString;
    timeText.setFont(IOhandler::getIOhandler().getFont2());
    timeText.setCharacterSize(70);
    timeText.setFillColor(Color::Red);
    
    //speed
    Text speedText;
    speedText.setFont(IOhandler::getIOhandler().getFont2());
    speedText.setCharacterSize(70);
    speedText.setFillColor(Color::Yellow);
    string speedString;
    float speed;
    
    //previous time
    Text previousTimeText;
    previousTimeText.setFont(IOhandler::getIOhandler().getFont2());
    previousTimeText.setCharacterSize(130);
    previousTimeText.setFillColor(Color::Blue);
    
    //main loop
    while (WINDOW.isOpen()) {
        
        Event event;
        while (WINDOW.pollEvent(event)) {
            if(event.type==Event::Closed) {
                WINDOW.close();
            }
        }
        
        myPlayer.up = 0;
        myPlayer.down = 0;
        myPlayer.left = 0;
        myPlayer.right = 0;
        
        //processing collisions and start line
        string previousLap = "";
        previousLap = processAllCollisions(level, levelNumber, timer);
        previousLap.resize(11);
        previousTimeText.setString(previousLap);
        previousTimeText.setPosition(viewCenter.x-(viewSize.x/2)+previousTimeText.getGlobalBounds().width/2,
                                     viewCenter.y-(viewSize.y/2)+300);
        
        //driving car
        if (myPlayer.drive()==false) return;
        
        //setting view
        setGameView();
        
        //speed
        speed = myPlayer.getSpeed();
        speedString = "Speed: " + to_string(speed);
        speedString.resize(11);
        speedText.setString(speedString);
        speedText.setPosition(viewCenter.x-(viewSize.x/2)+50, viewCenter.y-(viewSize.y/2)+50);
        
        //time text
        timeString = timer.showTime();
        timeText.setString(timeString);
        timeText.setPosition(viewCenter.x+(viewSize.x/2)-850, viewCenter.y-(viewSize.y/2)+50);
        
        //update the game
        WINDOW.clear();
        myPlayer.updatePosition();
        
        //draw objects
        WINDOW.draw(background);
        //draw map
        for (int j=0; j<IOhandler::getIOhandler().spriteTab[levelNumber]; j++) {
            WINDOW.draw(level.spriteMaps[levelNumber][j]);
        }
        WINDOW.draw(level.startLine);
        WINDOW.draw(myPlayer.getSprite());
        WINDOW.draw(speedText);
        WINDOW.draw(timeText);
        
        //show previous lap time
        if (timer.is5Seconds()==true) {
            if (previousLap[0]!='\0') { //when time is not set
                WINDOW.draw(previousTimeText);
            }
        }
        
        //display frame
        WINDOW.display();
    }
}

void Engine::runEngineRACE(int levelNumber) {
    
    resetRACE();

    //level
    LevelMap level(levelNumber);
    level.setMap();
    
    //opponents vector
    int opponentsNumber = GameSettings::getGameSettings().opponentsNumber;
    vector <Opponent> opponents;
    for (int i=0; i<opponentsNumber; i++) {
        Opponent opponent(i); //set position
        opponents.push_back(opponent);
    }
    
    //create car pointers vector
    vector <Car*> carsPtrVector;
    //adding player pointer
    Player* playerPtr;
    playerPtr = &myPlayer;
    carsPtrVector.push_back(playerPtr);
    //adding opponents pointers
    for (int i=0; i<opponentsNumber; i++) {
        Car* carPtr;
        carPtr = &opponents[i];
        carsPtrVector.push_back(carPtr);
    }
    
    //speed
    Text speedText;
    speedText.setFont(IOhandler::getIOhandler().getFont2());
    speedText.setCharacterSize(90);
    speedText.setFillColor(Color::Blue);
    string speedString;
    float speed;
    
    //laps completed
    string lapCompletedStr;
    Text lapsCompletedText;
    lapsCompletedText.setFont(IOhandler::getIOhandler().getFont2());
    lapsCompletedText.setCharacterSize(90);
    lapsCompletedText.setFillColor(Color::Red);

    //main loop
    while (WINDOW.isOpen()) {
        
        Event event;
        while (WINDOW.pollEvent(event)) {
            if(event.type==Event::Closed) {
                WINDOW.close();
            }
        }
        
        //set player controls
        myPlayer.up = 0;
        myPlayer.down = 0;
        myPlayer.left = 0;
        myPlayer.right = 0;
        
        //processing collisions and start line
        if (processAllCollisions(level, opponents, levelNumber, timer)==false) {
            showResults();
            return;
        }
        
        //driving cars
        for (int i=0; i<opponentsNumber+1; i++) {
            if (carsPtrVector[i]->drive()==false) return;
        }
        
        //setting view
        setGameView();
        
        //speed
        speed = myPlayer.getSpeed();
        speedString = "Speed: " + to_string(speed);
        speedString.resize(11);
        speedText.setString(speedString);
        speedText.setPosition(viewCenter.x-(viewSize.x/2)+50, viewCenter.y-(viewSize.y/2)+50);
        
        //laps completed
        if (myPlayer.lapCompleted==-1) lapCompletedStr = to_string(0);
        else lapCompletedStr = to_string(myPlayer.lapCompleted);
        lapCompletedStr = "Lap:" + lapCompletedStr + "/" + to_string(GameSettings::getGameSettings().lapNumber);
        lapsCompletedText.setString(lapCompletedStr);
        lapsCompletedText.setPosition(viewCenter.x-(viewSize.x/2)+3*lapsCompletedText.getGlobalBounds().width,
                                      viewCenter.y-(viewSize.y/2)+50);
        
        //update the game
        WINDOW.clear();
        myPlayer.updatePosition();
        
        //draw objects
        WINDOW.draw(background);
        //draw map
        for (int j=0; j<IOhandler::getIOhandler().spriteTab[levelNumber]; j++) {
            WINDOW.draw(level.spriteMaps[levelNumber][j]);
        }
        //draw opponents
        for (int i=0; i<opponents.size(); i++) {
            opponents[i].updatePosition();
            WINDOW.draw(opponents[i].getSprite());
        }
        WINDOW.draw(level.startLine);
        WINDOW.draw(myPlayer.getSprite());
        WINDOW.draw(speedText);
        WINDOW.draw(lapsCompletedText);
        
        //display frame
        WINDOW.display();
    }
}


void Engine::setGameView(void) {
    
    if (myPlayer.carPosition.x>RESOLUTION.x/2 &&
        myPlayer.carPosition.x<11000-RESOLUTION.x/2)
    {
        viewCenter.x = myPlayer.carPosition.x;
        view.setCenter(viewCenter);
        WINDOW.setView(view);
    }
    if (myPlayer.carPosition.y>RESOLUTION.y/2 &&
        myPlayer.carPosition.y<8000-RESOLUTION.y/2)
    {
        viewCenter.y = myPlayer.carPosition.y;
        view.setCenter(viewCenter);
        WINDOW.setView(view);
    }
}

string Engine::processAllCollisions(LevelMap& level, int levelNumber, Timer& timer) {
    processCurbCollisions(level, levelNumber);
    string previousLap = processStartLine(level, timer);
    return previousLap;
}

bool Engine::processAllCollisions(LevelMap& level, vector <Opponent>& opponents, int levelNumber, Timer& timer) {
    processCurbCollisions(level, levelNumber);
    processCarCollisions(opponents);
    for (int i=0; i<opponents.size(); i++) {
        if (processStartLine(level, opponents[i])==true) {
            if (opponents[i].atStartLine==false) {
                opponents[i].lapCompleted++;
                if (opponents[i].lapCompleted==GameSettings::getGameSettings().lapNumber) {
                    string str;
                    str = ". opponent " + to_string(i+1);
                    result.push_back(str);
                    opponentsReachedFinish++;
                }
                opponents[i].atStartLine = true;
            }
        }
        else {
            if (opponents[i].atStartLine==true) opponents[i].atStartLine = false;
        }
    }
    
    if (processStartLine(level)==true) {
        if (myPlayer.atStartLine==false) {
            myPlayer.lapCompleted++;
            if (myPlayer.lapCompleted==GameSettings::getGameSettings().lapNumber) {
                string str;
                str = ". player";
                result.push_back(str);
                return false;
            }
            myPlayer.atStartLine = true;
        }
    }
    else {
        if (myPlayer.atStartLine==true) myPlayer.atStartLine = false;
    }
    
    return true;
}

void Engine::showResults() {

    viewCenter.operator=(Vector2f(RESOLUTION.x/2, RESOLUTION.y/2)); //to set view in start
    view.setCenter(viewCenter);
    Text resultText;
    string resultString = "";
    resultText.setFont(IOhandler::getIOhandler().getFont2());
    resultText.setCharacterSize(90);
    resultText.setFillColor(Color::Red);
    
    for (int i=0; i<opponentsReachedFinish+1; i++) {
        resultString.append(to_string(i+1) + result[i] + "\n");
    }
    resultText.setString(resultString);
    resultText.setPosition((RESOLUTION.x/2)-(resultText.getGlobalBounds().width/2), RESOLUTION.y/6);
    
    //exit result screen by pressing space
    Event event;
    while(true) {
        while ( WINDOW.pollEvent(event) ) {
            switch (event.type) {
                case (Event::KeyPressed):
                if(event.key.code==Keyboard::Space) {
                    return;
                }
                default: break;
            }
        }
        WINDOW.clear();
        WINDOW.setView(view);
        WINDOW.draw(resultText);
        WINDOW.display();
    }
}

void Engine::processCurbCollisions(LevelMap& level, int levelNumber) {
    bool intersection = false;
    int i;
    for (i=0; i<IOhandler::getIOhandler().spriteTab[levelNumber]; i++) {
        //intersection
        if (level.spriteMaps[levelNumber][i].getGlobalBounds().contains(myPlayer.car.getPosition())) {
            intersection = true;
            break;
        }
    }
    if (intersection==true) {
        if (level.spriteMaps[levelNumber][i].getRotation()==90) {
            if ( (myPlayer.angle<M_PI_2) || (myPlayer.angle>3*M_PI_2) ) {
                myPlayer.angle = 0;
            }
            else {
                myPlayer.angle = M_PI;
            }
        }
        else {
            if ( ((myPlayer.angle<M_PI)&&(myPlayer.angle>M_PI_2)) || (myPlayer.angle<M_PI_2) ) {
                myPlayer.angle = M_PI_2;
            }
            else {
                myPlayer.angle = 3*M_PI_2;
            }
        }
    }
}

string Engine::processStartLine(LevelMap& level, Timer& timer) {
    bool intersection = false;
    string previousLap;
    previousLap = timer.getPreviousLap(); 
    if (level.startLine.getGlobalBounds().intersects(myPlayer.getSprite().getGlobalBounds())) {
        intersection = true;
    }
    
    if (intersection==true) {
        previousLap = timer.stop();
        timer.start();
    }
    return previousLap;
}

bool Engine::processStartLine(LevelMap& level, Opponent opponent) {
    if (level.startLine.getGlobalBounds().intersects(opponent.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

bool Engine::processStartLine(LevelMap& level) {
    if (level.startLine.getGlobalBounds().intersects(myPlayer.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

void Engine::processCarCollisions(vector <Opponent>& opponents) {
    //player and opponents
    int d = 20;
    for (int i=0; i<opponents.size(); i++) {
        if (myPlayer.getSprite().getGlobalBounds().intersects(opponents[i].getSprite().getGlobalBounds())) {
            Vector2f offset;
            offset.x = (myPlayer.getSprite().getPosition().x - opponents[i].getSprite().getPosition().x)/d;
            offset.y = (myPlayer.getSprite().getPosition().y - opponents[i].getSprite().getPosition().y)/d;
            myPlayer.carPosition.x += offset.x;
            myPlayer.carPosition.y += offset.y;
            opponents[i].carPosition.x -= offset.x;
            opponents[i].carPosition.y -= offset.y;
        }
    }
    
    //opponents
    for (int i=0; i<opponents.size(); i++) {
        for (int j=0; j<opponents.size(); j++) {
            if (opponents[i].getSprite().getGlobalBounds().intersects(opponents[j].getSprite().getGlobalBounds())) {
                Vector2f offset;
                offset.x = (opponents[i].getSprite().getPosition().x - opponents[j].getSprite().getPosition().x)/d;
                offset.y = (opponents[i].getSprite().getPosition().y - opponents[j].getSprite().getPosition().y)/d;
                opponents[i].carPosition.x += offset.x;
                opponents[i].carPosition.y += offset.y;
                opponents[j].carPosition.x -= offset.x;
                opponents[j].carPosition.y -= offset.y;
            }
        }
    }
}

void Engine::resetTT() {
    myPlayer.reset();
    viewCenter.operator=(Vector2f(4900, 7200)); //to set view on start
    view.setCenter(viewCenter);
    setGameView();
    WINDOW.setView(view);
    timer.reset();
}

void Engine::resetRACE() {
    resetTT();
    opponentsReachedFinish = 0;
    myPlayer.lapCompleted = -1;
    result.clear();
    timer.reset();
}
