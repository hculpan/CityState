//
//  game.h
//  ProgrammedParties
//
//  Created by Harry Culpan on 7/5/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <iostream>

// Set value to next available increment
#define CLEAR_TILE      0
#define WOOD_TILE       1

// These are OR'd, so should be powers of two
#define HUT             1

class Game {
private:
    const int bLeft = 385;
    const int bTop = 88;
    const int bRight = 1185;
    const int bBottom = 888;

public:
    // resources
    int food;
    int wood;
    int stone;
    int metal;
    
    int tools;
    int laborers;
    
    int gatherFood;
    int gatherWood;
    int gatherStone;
    int gatherMetal;
    int makeTools;
    int totalGather;
    
    int screenWidth;
    int screenHeight;
    
    bool paused = false;
    bool changed = false;
    bool quitting = false;
    
    const std::string resourcePath = std::string("/Users/harryculpan/src/CityState/CityState/resources/");

    Game(const int screenWidth, const int screenHeight);
    
    bool isPaused() const { return paused; }
    void pausedHit() { paused = !paused; }
    
    void laborerGatherFood();
    void laborerUngatherFood();
    void laborerGatherWood();
    void laborerUngatherWood();
    void laborerGatherStone();
    void laborerUngatherStone();
    void laborerGatherMetal();
    void laborerUngatherMetal();

    bool laborersAvailable();
    
    void reset();
    
    void update();
};

extern Game *game;

extern double dpiModifier;

#endif /* game_h */
