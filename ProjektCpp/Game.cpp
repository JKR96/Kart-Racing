//
//  Game.cpp
//  ProjektCpp
//
//  Created by Jakub Radziwiński on 15.11.2017.
//  Copyright © 2017 Jakub Radziwiński. All rights reserved.
//

#include "Game.hpp"

Game::Game(void) {
    GameSettings::getGameSettings();
    GameSettings::getGameSettings().setAllLevels(IOhandler::getIOhandler().allLevels);
    
    state = MENU; //menu first
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Game::~Game(void) {
    Text loading;
    loading.setFont(IOhandler::getIOhandler().getFont1());
    loading.setCharacterSize(150);
    loading.setString("Goodbye!");
    loading.setPosition((RESOLUTION.x/2)-(loading.getGlobalBounds().width/2), RESOLUTION.y/2.4);
    loading.setFillColor(Color::Red);
    WINDOW.clear(Color::Black);
    WINDOW.draw(loading);
    WINDOW.display();
    this_thread::sleep_for(chrono::milliseconds(800));
    WINDOW.close();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::runGame(void) {
    
    menuState = S1;
    firstScreen();
    while (true) {
        state = displayMenu(menuState);
        switch (state) {
            case MENU:
                break;
                
            case TT:
                timeTrial();
                break;
                
            case RACE:
                race();
                break;
                
            case SETTINGS:
                settings();
                break;
                
            case ABOUT:
                about();
                break;
                
            case END:
                return;
                
            default:
                break;
        }
        WINDOW.setView(WINDOW.getDefaultView());
    }
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::firstScreen() {
    
    Text title, sign, press;
    title.setFont(IOhandler::getIOhandler().getFont1());
    title.setString("Kart Racing");
    title.setCharacterSize(250);
    title.setFillColor(Color::Red);
    title.setPosition((RESOLUTION.x/2)-(title.getGlobalBounds().width/2), RESOLUTION.y/3);
    
    sign.setFont(IOhandler::getIOhandler().getFont2());
    sign.setString("created by: J K R");
    sign.setCharacterSize(40);
    sign.setFillColor(Color::Red);
    sign.setPosition(RESOLUTION.x/1.8, RESOLUTION.y/1.8);
    
    press.setFont(IOhandler::getIOhandler().getFont2());
    press.setString("<press Space to continue>");
    press.setCharacterSize(30);
    press.setFillColor(Color::White);
    press.setPosition( (RESOLUTION.x/2)-(press.getGlobalBounds().width/2), RESOLUTION.y/1.1);
    
    //exit first screen by pressing space
    Event event;
    while(state==MENU) {
        while ( WINDOW.pollEvent(event) ) {
            switch (event.type) {
                case (Event::KeyPressed):
                    if(event.key.code==Keyboard::Space) {
                        state = MENU;
                        return;
                    }
                default: break;
            }
        }
        
        //update the game
        WINDOW.clear();
        //draw objects here
        WINDOW.draw(title);
        WINDOW.draw(sign);
        WINDOW.draw(press);
        WINDOW.display();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Game::GameState Game::displayMenu(MenuState) {
    
    //set game state
    GameState state = GameState::MENU;
    
    //setting menu texts
    const int count = 5;
    vector <Text> text;
    string str[] = {"Time Trial", "Race", "Settings", "About", "Exit"};
    
    for (int i=0; i<count; i++) {
        Text t;
        text.push_back(t);
    }
    
    //main loop
    while ( WINDOW.isOpen() ) {
        Event event;
        
        for(int i=0; i<count; i++) {
            text[i].setFont(IOhandler::getIOhandler().getFont1());
            text[i].setString(str[i]);
            text[i].setCharacterSize(55);
            text[i].setFillColor(Color(130, 3, 3));
            text[i].setPosition((RESOLUTION.x/2)-(text[i].getGlobalBounds().width/2),
                                (RESOLUTION.y/7.5*i)+300);
        }
        
        //setting choice highlighting
        text[menuState].setFillColor(Color(255, 1, 1));
        text[menuState].setCharacterSize(80);
        text[menuState].setPosition((RESOLUTION.x/2)-(text[menuState].getGlobalBounds().width/2),
                                    (RESOLUTION.y/7.5*menuState)+260);

        //side sprites
        Sprite sprite1(IOhandler::getIOhandler().getMenu1()), sprite2(IOhandler::getIOhandler().getMenu2());
        sprite1.scale(0.5f, 0.5f);
        sprite2.scale(0.5f, 0.5f);
        sprite1.setPosition(0, RESOLUTION.y/2-sprite1.getGlobalBounds().height/2);
        sprite2.setPosition(RESOLUTION.x - sprite2.getGlobalBounds().width, RESOLUTION.y/2-sprite2.getGlobalBounds().height/2);
        
        //handling input data
        while ( WINDOW.pollEvent(event) ) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if(event.key.code==Keyboard::Up) {
                        menuState = decrement(menuState);
                        break;
                    }
                    else if(event.key.code==Keyboard::Down) {
                        menuState = increment(menuState);
                        break;
                    }
                    else if(event.key.code==Keyboard::Return) {
                        state = setGameState(menuState);
                        return state;
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        //update the game
        WINDOW.clear();
        
        //draw objects here
        for(int i=0; i<count; i++) {
            WINDOW.draw(text[i]);
        }
        WINDOW.draw(sprite1);
        WINDOW.draw(sprite2);
        WINDOW.display();
    }
    return state;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::about(void) {
    
    //set game state
    GameState state = GameState::ABOUT;
    string textString = "Time Trial - try to set the best time\nRace - first reach the finish line\n\n"
    "Vehicle control:\nUp - accelerate\nDown - brake\nLeft - turn left\nRight - turn right\n"
    "\n\n\n                                         created by JKR\n"
    "                                         powered by SFML";
    
    Text title, text;
    title.setFont(IOhandler::getIOhandler().getFont1());
    title.setString("Kart Racing");
    title.setCharacterSize(130);
    title.setFillColor(Color::Red);
    title.setPosition((RESOLUTION.x/2)-(title.getGlobalBounds().width/2), RESOLUTION.y/9);
    
    text.setFont(IOhandler::getIOhandler().getFont2());
    text.setString(textString);
    text.setCharacterSize(43);
    text.setFillColor(Color::Red);
    text.setPosition((RESOLUTION.x/2)-(text.getGlobalBounds().width/2), RESOLUTION.y/2.5);
    
    Event event;
    while(state==ABOUT) {
        while ( WINDOW.pollEvent(event) ) {
            switch (event.type) {
                case (Event::KeyPressed):
                    if(event.key.code==Keyboard::Escape) {
                        state = MENU;
                        return;
                    }
                default: break;
            }
        }
        
        //update the game
        WINDOW.clear();
        //draw objects here
        WINDOW.draw(title);
        WINDOW.draw(text);
        WINDOW.display();
    }
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::settings() {
    
    //set game state
    GameState state = GameState::SETTINGS;
    
    //selected setting
    int setting = 0;

    //main loop
    while ( WINDOW.isOpen() ) {
        Event event;
        
        //setting texts
        string difficultyString[] = {"Easy", "Medium", "Hard", "Expert"};
        string str[] = {"Level number: " + to_string(GameSettings::getGameSettings().levelNumber+1),
            "Number of laps: " + to_string(GameSettings::getGameSettings().lapNumber),
            "Number of opponents: " + to_string(GameSettings::getGameSettings().opponentsNumber),
            "Difficulty level: " + difficultyString[GameSettings::getGameSettings().difficulty]};
        
        const int textSize = 4;
        vector <Text> textVector;
        for (int i=0; i<textSize; i++) {
            Text text;
            textVector.push_back(text);
        }
        
        for(int i=0; i<textSize; i++) {
            textVector[i].setFont(IOhandler::getIOhandler().getFont2());
            textVector[i].setString(str[i]);
            textVector[i].setCharacterSize(40);
            textVector[i].setFillColor(Color(130, 3, 3));
            textVector[i].setPosition((RESOLUTION.x/2)-(textVector[i].getGlobalBounds().width/2),
                                      (RESOLUTION.y/7.5*i)+300);
        }
        
        //setting choice highlighting
        textVector[setting].setFillColor(Color(255, 1, 1));
        textVector[setting].setCharacterSize(50);
        textVector[setting].setStyle(sf::Text::Bold);
        textVector[setting].setPosition((RESOLUTION.x/2)-(textVector[setting].getGlobalBounds().width/2),
                                    (RESOLUTION.y/7.5*setting)+260);
        
        //side sprites
        Sprite sprite1(IOhandler::getIOhandler().getMenu1()), sprite2(IOhandler::getIOhandler().getMenu2());
        sprite1.setPosition(0, 0);
        sprite2.setPosition(RESOLUTION.x - sprite2.getGlobalBounds().width, 0);
        
        //handling input data
        while (WINDOW.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code==Keyboard::Up) {
                        setting--;
                        break;
                    }
                    else if (event.key.code==Keyboard::Down) {
                        setting++;
                        break;
                    }
                    else if (event.key.code==Keyboard::Left) {
                        switch (setting) {
                            case 0:
                                if (GameSettings::getGameSettings().levelNumber>0)
                                GameSettings::getGameSettings().levelNumber--;
                                break;
                                
                            case 1:
                                if (GameSettings::getGameSettings().lapNumber>1)
                                GameSettings::getGameSettings().lapNumber--;
                                break;
                                
                            case 2:
                                if (GameSettings::getGameSettings().opponentsNumber>1)
                                GameSettings::getGameSettings().opponentsNumber--;
                                break;
                                
                            case 3:
                                GameSettings::getGameSettings().difficulty = decrement(GameSettings::getGameSettings().difficulty);
                                break;
                                
                            default:
                                break;
                        }
                    }
                    else if (event.key.code==Keyboard::Right) {
                        switch (setting) {
                            case 0:
                                if(GameSettings::getGameSettings().levelNumber<GameSettings::getGameSettings().allLevels-1)
                                GameSettings::getGameSettings().levelNumber++;
                                break;
                                
                            case 1:
                                if (GameSettings::getGameSettings().lapNumber<10)
                                GameSettings::getGameSettings().lapNumber++;
                                break;
                                
                            case 2:
                                if (GameSettings::getGameSettings().opponentsNumber<7)
                                GameSettings::getGameSettings().opponentsNumber++;
                                break;
                                
                            case 3:
                                GameSettings::getGameSettings().difficulty = increment(GameSettings::getGameSettings().difficulty);
                                break;
                                
                            default:
                                break;
                        }
                        break;
                    }
                    else if (event.key.code==Keyboard::Escape) {
                        state = GameState::MENU;
                        return;
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        //update the game
        WINDOW.clear();
        
        //draw objects here
        for(int i=0; i<textSize; i++) {
            WINDOW.draw(textVector[i]);
        }
        WINDOW.draw(sprite1);
        WINDOW.draw(sprite2);
        
        WINDOW.display();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::timeTrial(void) {
    int levelNumber = GameSettings::getGameSettings().levelNumber;
    gameEngine.runEngineTT(levelNumber);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::race(void) {
    int levelNumber = GameSettings::getGameSettings().levelNumber;
    gameEngine.runEngineRACE(levelNumber);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Game::MenuState Game::increment(MenuState menuState) {
    switch(menuState) {
        case S1:
            return S2;
            
        case S2:
            return S3;
            
        case S3:
            return S4;
            
        case S4:
            return S5;
            
        case S5:
            return S5;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Game::MenuState Game::decrement(MenuState menuState) {
    switch(menuState) {
        case S1:
            return S1;
            
        case S2:
            return S1;
            
        case S3:
            return S2;
            
        case S4:
            return S3;
            
        case S5:
            return S4;
    }
}

GameSettings::DifficultyLevel Game::increment(GameSettings::DifficultyLevel difficulty) {
    switch(difficulty) {
        case GameSettings::EASY:
            return GameSettings::MEDIUM;
            
        case GameSettings::MEDIUM:
            return GameSettings::HARD;
            
        case GameSettings::HARD:
            return GameSettings::EXPERT;
            
        case GameSettings::EXPERT:
            return GameSettings::EXPERT;
            
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameSettings::DifficultyLevel Game::decrement(GameSettings::DifficultyLevel difficulty) {
    switch(difficulty) {
        case GameSettings::EASY:
            return GameSettings::EASY;
            
        case GameSettings::MEDIUM:
            return GameSettings::EASY;
            
        case GameSettings::HARD:
            return GameSettings::MEDIUM;
            
        case GameSettings::EXPERT:
            return GameSettings::HARD;
            
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Game::GameState Game::setGameState(MenuState menuState) {
    switch(menuState) {
        case S1:
            return TT;
            
        case S2:
            return RACE;
            
        case S3:
            return SETTINGS;
            
        case S4:
            return ABOUT;
            
        case S5:
            return END;
    }
}
