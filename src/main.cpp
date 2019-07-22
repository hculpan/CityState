//
//  main.cpp
//  ProgrammedParties
//
//  Created by Harry Culpan on 7/3/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>

#include "Game.hpp"
#include "MainWindow.hpp"
#include "FontManager.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1240;
const int SCREEN_HEIGHT = 940;

void logSDLError(const std::string &msg);
bool initGraphics();

MainWindow *mainWindow;

int main(int argc, const char * argv[]) {
    if (!initGraphics()) {
        return 1;
    };
    
    game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->reset();
    fontManager->initialize();
    mainWindow = new MainWindow();
    
    SDL_Event e;
    while (!game->quitting){
        while (SDL_PollEvent(&e)){
            mainWindow->handleEvent(&e);
            if (game->quitting) {
                break;
            }
        }
        
        if (!game->isPaused()) {
            // Called by Next Turn button event
//            game->update();
        }
        mainWindow->render(false);
    }

    mainWindow->cleanup();
    return 0;
}

void logSDLError(const std::string &msg) {
    std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

bool initGraphics() {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
        logSDLError("SDL_Init");
        return false;
    }
    
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError("IMG_Init");
        SDL_Quit();
        return false;
    }
    
    if (TTF_Init() != 0){
        logSDLError("TTF_Init");
        SDL_Quit();
        return false;
    }
    
    return true;
}

