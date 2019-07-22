//
//  MainWindow.hpp
//  ProgrammedParties
//
//  Created by Harry Culpan on 7/5/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#ifndef MainWindow_hpp
#define MainWindow_hpp

#include "Window.hpp"
#include "Button.hpp"
#include "TextOutput.hpp"

class MainWindow : public Window {
private:
    static const int MAP_SIZE = 11;
    
    SDL_Window *window;
    SDL_Texture *map;
    
    SDL_Texture *clearTile;
    SDL_Texture *woodTile;
    SDL_Texture *unknownTile;
    
    SDL_Texture *laborer;
    SDL_Texture *hut;
    
    int mapTiles[MAP_SIZE][MAP_SIZE];
    bool mapUnknown[MAP_SIZE][MAP_SIZE];
    bool mapSelected[MAP_SIZE][MAP_SIZE];
    int mapLaborers[MAP_SIZE][MAP_SIZE];
    int mapFeatures[MAP_SIZE][MAP_SIZE];
    
    bool quitButtonClicked = false;
    
    Button *quitButton;
    Button *newGameButton;
    Button *nextTurnButton;
    
    Button *gatherFoodButton;
    Button *ungatherFoodButton;
    
    Button *gatherWoodButton;
    Button *ungatherWoodButton;
    
    Button *gatherStoneButton;
    Button *ungatherStoneButton;
    
    Button *gatherMetalButton;
    Button *ungatherMetalButton;
    
    TextOutput *laborersLabel;
    TextOutput *laborersValue;
    TextOutput *laborersWorkers;

    TextOutput *foodLabel;
    TextOutput *foodValue;
    TextOutput *foodWorkers;

    TextOutput *woodLabel;
    TextOutput *woodValue;
    TextOutput *woodWorkers;
    
    TextOutput *stoneLabel;
    TextOutput *stoneValue;
    TextOutput *stoneWorkers;
    
    TextOutput *metalLabel;
    TextOutput *metalValue;
    TextOutput *metalWorkers;
    
    void updateText(TextOutput *label, TextOutput *valueText, TextOutput *laborersText, Button *gatherButton, Button *ungatherButton, const std::string &msg, int y, int value, int workers);
    
    void loadTextures();
    
    void createLabels();
    
    void initializeData();
    
    void renderTiles();
    
    void setSelectedMap(int x, int y);
    
    inline void setFeature(int x, int y, int feature) { mapFeatures[x][y] |= feature; }
    
    inline bool hasFeature(int x, int y, int feature) { return mapFeatures[x][y] & feature; }
    
public:
    MainWindow();
    
    void updateStatus();
    
    virtual void render(bool forceRedraw);
    virtual void cleanup();
    virtual bool handleEvent(SDL_Event *e);
};

#endif /* MainWindow_hpp */
