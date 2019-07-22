//
//  game.cpp
//  ProgrammedParties
//
//  Created by Harry Culpan on 7/5/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#include "Game.hpp"

double dpiModifier = 1.0;

Game *game = nullptr;

Game::Game(const int screenWidth, const int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void Game::reset() {
    food = 10;
    wood = 10;
    stone = 0;
    metal = 0;
    tools = 0;
    laborers = 5;
    
    gatherFood = 0;
    gatherWood = 0;
    gatherStone = 0;
    gatherMetal = 0;
    makeTools = 0;
    totalGather = 0;
    
    paused = false;
}

void Game::update() {
    food -= laborers;
    if (food < 0) {
        laborers += food;
        food = 0;
    }
    
    food += gatherFood * 2;
    wood += gatherWood * 2;
    stone += gatherStone;
    metal += gatherMetal/2;
    
    gatherFood = 0;
    gatherWood = 0;
    gatherStone = 0;
    gatherMetal = 0;
    makeTools = 0;
    totalGather = 0;
}

void Game::laborerGatherFood() {
    if (laborersAvailable()) {
        gatherFood++;
        totalGather++;
    }
}

void Game::laborerUngatherFood() {
    if (gatherFood > 0) {
        gatherFood--;
        totalGather--;
    }
}

void Game::laborerGatherWood() {
    if (laborersAvailable()) {
        gatherWood++;
        totalGather++;
    }
}

void Game::laborerUngatherWood() {
    if (gatherWood > 0) {
        gatherWood--;
        totalGather--;
    }
}

void Game::laborerGatherStone() {
    if (laborersAvailable()) {
        gatherStone++;
        totalGather++;
    }
}

void Game::laborerUngatherStone() {
    if (gatherStone > 0) {
        gatherStone--;
        totalGather--;
    }
}

void Game::laborerGatherMetal() {
    if (laborersAvailable()) {
        gatherMetal++;
        totalGather++;
    }
}

void Game::laborerUngatherMetal() {
    if (gatherMetal > 0) {
        gatherMetal--;
        totalGather--;
    }
}

bool Game::laborersAvailable() {
    return (gatherFood + gatherWood + gatherStone + gatherMetal < laborers);
}
