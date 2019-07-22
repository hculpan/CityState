//
//  MainWindow.cpp
//  ProgrammedParties
//
//  Created by Harry Culpan on 7/5/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#include "MainWindow.hpp"
#include "Game.hpp"

#include <SDL2/SDL.h>

#include <sstream>
#include <iterator>

#define MAP_START_X 405
#define MAP_START_Y 110

bool MainWindow::handleEvent(SDL_Event *e) {
    std::list<Window *>::iterator i;
    bool eventHandled = false;

    for(i = children.begin(); i != children.end(); ++i) {
        eventHandled = (*i)->handleEvent(e);
        if (eventHandled)
            break;
    }
    
    if (!eventHandled) {
        if (e->type == SDL_QUIT){
            game->quitting = true;
            eventHandled = true;
            cleanup();
        } else if (e->type == SDL_KEYDOWN){
            if (e->key.keysym.sym == SDLK_SPACE) {
                game->pausedHit();
                eventHandled = true;
            }
        } else if (e->type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x > (MAP_START_X * dpiModifier) && y > (MAP_START_Y * dpiModifier)) {
                x = (x - MAP_START_X) / 73;
                y = (y - MAP_START_Y) / 73;
                setSelectedMap(x, y);
                eventHandled = true;
            }
        } else if (e->type == SDL_WINDOWEVENT) {
            if (e->window.event == SDL_WINDOWEVENT_MINIMIZED && !game->isPaused()) {
                game->pausedHit();
                eventHandled = true;
            } else if (e->window.event == SDL_WINDOWEVENT_FOCUS_GAINED && game->isPaused()) {
                game->pausedHit();
                eventHandled = true;
            }
        }
    }
    
    return eventHandled;
}

void MainWindow::updateText(TextOutput *label, TextOutput *valueText, TextOutput *laborersText, Button *gatherButton, Button *ungatherButton, const std::string &msg, int y, int value, int workers) {
    
    label->setPositions((16 * dpiModifier), (y * dpiModifier));
    label->setFontSize(18);
    label->setText(msg);
    
    valueText->setPositions((130 * dpiModifier), (y * dpiModifier));
    valueText->setFontSize(18);
    valueText->setText(std::to_string(value));
    
    if (laborersText) {
        laborersText->setFontSize(18);
        laborersText->setPositions((250 * dpiModifier), (y * dpiModifier));
        laborersText->setText(std::to_string(workers));
    }
    
    if (gatherButton) {
        gatherButton->setPositions((280 * dpiModifier), ((y + 4) * dpiModifier));
    }
    
    if (ungatherButton) {
        ungatherButton->setPositions((305 * dpiModifier), ((y + 4) * dpiModifier));
    }
}

void MainWindow::updateStatus() {
    updateText(laborersLabel, laborersValue, laborersWorkers, NULL, NULL, "Laborers: ", 142, game->laborers - game->totalGather, game->totalGather);
    updateText(foodLabel, foodValue, foodWorkers, gatherFoodButton, ungatherFoodButton, "Food: ", 190, game->food, game->gatherFood);
    updateText(woodLabel, woodValue, woodWorkers, gatherWoodButton, ungatherWoodButton, "Wood: ", 238, game->wood, game->gatherWood);
    updateText(stoneLabel, stoneValue, stoneWorkers, gatherStoneButton, ungatherStoneButton, "Stone: ", 286, game->stone, game->gatherStone);
    updateText(metalLabel, metalValue, metalWorkers, gatherMetalButton, ungatherMetalButton, "Metal: ", 334, game->metal, game->gatherMetal);
}

void MainWindow::initializeData() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            mapTiles[i][j] = WOOD_TILE;
            mapUnknown[i][j] = true;
            mapSelected[i][j] = false;
            mapLaborers[i][j] = 0;
            mapFeatures[i][j] = 0;
        }
    }
    
    mapTiles[5][5] = CLEAR_TILE;
    mapLaborers[5][5] = 5;
    setFeature(5, 5, HUT);
    
    mapUnknown[4][4] = false;
    mapUnknown[4][5] = false;
    mapUnknown[4][6] = false;
    mapUnknown[5][4] = false;
    mapUnknown[5][5] = false;
    mapUnknown[5][6] = false;
    mapUnknown[6][4] = false;
    mapUnknown[6][5] = false;
    mapUnknown[6][6] = false;
}

MainWindow::MainWindow() : Window() {
    initializeData();
    
    //Create window
    window = SDL_CreateWindow(
                                          "City-State",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          game->screenWidth,
                                          game->screenHeight,
                              SDL_WINDOW_SHOWN); // | SDL_WINDOW_ALLOW_HIGHDPI);
    if( window == nullptr ) {
        logSDLError("CreateWindow");
        SDL_Quit();
    }
    
    int w, h;
    SDL_GL_GetDrawableSize(window, &w, &h);
    // dpiModifier = w / game->screenWidth;
    dpiModifier = 1.0;
    // game->screenWidth = w;
    // game->screenHeight = h;
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError("CreateRenderer");
        SDL_Quit();
    }
    
    quitButton = new Button(this, game->screenWidth - (121 * dpiModifier), (12 * dpiModifier), "QuitButton", [](Window *context, SDL_Event *e) {
        SDL_Event qe;
        qe.type = SDL_QUIT;
        SDL_PushEvent(&qe);
        return true;
    });
    newGameButton = new Button(this, game->screenWidth - (230 * dpiModifier), (12 * dpiModifier), "NewGameButton", [](Window *context, SDL_Event *e) {
        game->reset();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    nextTurnButton = new Button(this, (16 * dpiModifier), (12 * dpiModifier), "NextTurnButton", [](Window *context, SDL_Event *e) {
        game->update();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    gatherFoodButton = new Button(this, (10 * dpiModifier), (190 * dpiModifier), "GatherButton", [](Window *context, SDL_Event *e) {
        game->laborerGatherFood();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    ungatherFoodButton = new Button(this, (10 * dpiModifier), (190 * dpiModifier), "UngatherButton", [](Window *context, SDL_Event *e) {
        game->laborerUngatherFood();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    gatherWoodButton = new Button(this, (270 * dpiModifier), (238 * dpiModifier), "GatherButton", [](Window *context, SDL_Event *e) {
        game->laborerGatherWood();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    ungatherWoodButton = new Button(this, (10 * dpiModifier), (238 * dpiModifier), "UngatherButton", [](Window *context, SDL_Event *e) {
        game->laborerUngatherWood();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    gatherStoneButton = new Button(this, (270 * dpiModifier), (238 * dpiModifier), "GatherButton", [](Window *context, SDL_Event *e) {
        game->laborerGatherStone();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    ungatherStoneButton = new Button(this, (10 * dpiModifier), (238 * dpiModifier), "UngatherButton", [](Window *context, SDL_Event *e) {
        game->laborerUngatherStone();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    gatherMetalButton = new Button(this, (270 * dpiModifier), (238 * dpiModifier), "GatherButton", [](Window *context, SDL_Event *e) {
        game->laborerGatherMetal();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    ungatherMetalButton = new Button(this, (10 * dpiModifier), (238 * dpiModifier), "UngatherButton", [](Window *context, SDL_Event *e) {
        game->laborerUngatherMetal();
        reinterpret_cast<MainWindow *>(context->getParent())->updateStatus();
        return true;
    });
    
    createLabels();
    
    updateStatus();

    loadTextures();
}

void MainWindow::createLabels() {
    laborersLabel = new TextOutput(this);
    laborersValue = new TextOutput(this);
    laborersWorkers = new TextOutput(this);
    laborersWorkers->setForegroundColor({255, 0, 0, 255});
    foodLabel = new TextOutput(this);
    foodValue = new TextOutput(this);
    foodWorkers = new TextOutput(this);
    foodWorkers->setForegroundColor({255, 0, 0, 255});
    woodLabel = new TextOutput(this);
    woodValue = new TextOutput(this);
    woodWorkers = new TextOutput(this);
    woodWorkers->setForegroundColor({255, 0, 0, 255});
    stoneLabel = new TextOutput(this);
    stoneValue = new TextOutput(this);
    stoneWorkers = new TextOutput(this);
    stoneWorkers->setForegroundColor({255, 0, 0, 255});
    metalLabel = new TextOutput(this);
    metalValue = new TextOutput(this);
    metalWorkers = new TextOutput(this);
    metalWorkers->setForegroundColor({255, 0, 0, 255});
}

void MainWindow::loadTextures() {
    map = loadTexture(game->resourcePath + "MapBase.png", renderer);
    if (map == nullptr){
        logSDLError("LoadTexture:map");
        SDL_Quit();
    }

    clearTile = loadTexture(game->resourcePath + "ClearTile.png", renderer);
    if (clearTile == nullptr){
        logSDLError("LoadTexture:clearTile");
        SDL_Quit();
    }

    woodTile = loadTexture(game->resourcePath + "WoodTile.png", renderer);
    if (woodTile == nullptr){
        logSDLError("LoadTexture:woodTile");
        SDL_Quit();
    }

    unknownTile = loadTexture(game->resourcePath + "UnknownTile.png", renderer);
    if (unknownTile == nullptr){
        logSDLError("LoadTexture:unknownTile");
        SDL_Quit();
    }

    laborer = loadTexture(game->resourcePath + "Laborer.png", renderer);
    if (laborer == nullptr){
        logSDLError("LoadTexture:laborer");
        SDL_Quit();
    }

    hut = loadTexture(game->resourcePath + "Hut.png", renderer);
    if (hut == nullptr){
        logSDLError("LoadTexture:hut");
        SDL_Quit();
    }
}

void MainWindow::cleanup() {
    std::list<Window *>::iterator i;
    for(i = children.begin(); i != children.end(); ++i) {
        (*i)->cleanup();
    }
    
    SDL_DestroyTexture(map);
    SDL_DestroyTexture(clearTile);
    SDL_DestroyTexture(woodTile);
    SDL_DestroyTexture(unknownTile);
    SDL_DestroyTexture(laborer);
    SDL_DestroyTexture(hut);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void MainWindow::setSelectedMap(int x, int y) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == x && j == y) {
                mapSelected[i][j] = !mapSelected[i][j];
            } else {
                mapSelected[i][j] = false;
            }
        }
    }
}

void MainWindow::renderTiles() {
    renderTexture(map, renderer, ((MAP_START_X - 1) * dpiModifier), ((MAP_START_Y - 1) * dpiModifier));
    
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            int x = (MAP_START_X * dpiModifier) + (72 * dpiModifier * i) + i;
            int y = (MAP_START_Y * dpiModifier) + (72 * dpiModifier * j) + j;
            
            if (mapUnknown[i][j]) {
                renderTexture(unknownTile, renderer, x, y);
            } else if (mapTiles[i][j] == CLEAR_TILE) {
                renderTexture(clearTile, renderer, x, y);
            } else if (mapTiles[i][j] == WOOD_TILE) {
                renderTexture(woodTile, renderer, x, y);
            }
        }
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            int x = (MAP_START_X * dpiModifier) + (72 * dpiModifier * i) + i;
            int y = (MAP_START_Y * dpiModifier) + (72 * dpiModifier * j) + j;
            if (mapSelected[i][j]) {
                SDL_Rect rect;
                rect.x = x - 1;
                rect.y = y - 1;
                rect.w = 74;
                rect.h = 74;
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
            
            if (hasFeature(i, j, HUT)) {
                int lx, ly;
                ly = y + 1;
                lx = x + 1;
                renderTexture(hut, renderer, lx, ly);
            }
        }
    }
    

}

void MainWindow::render(bool forceRedraw) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    renderTiles();
    
    std::list<Window *>::iterator i;
    for(i = children.begin(); i != children.end(); ++i) {
        (*i)->render(forceRedraw);
    }

    SDL_RenderPresent(renderer);
}

