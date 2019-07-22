//
//  Button.cpp
//  CityState
//
//  Created by Harry Culpan on 7/7/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#include "Button.hpp"
#include "Game.hpp"

Button::Button(Window *parent, int x, int y, std::string textureFile, EventHandlerFunc eventHandler) : Component(parent) {
    this->eventHandler = eventHandler;
    this->x = x;
    this->y = y;
    
    activeTexture = loadTexture(game->resourcePath + textureFile + "Clicked.png", getRenderer());
    if (activeTexture == nullptr){
        logSDLError("LoadTexture:button");
        SDL_Quit();
    }
    
    inactiveTexture = loadTexture(game->resourcePath + textureFile + "Unclicked.png", getRenderer());
    if (inactiveTexture == nullptr){
        logSDLError("LoadTexture:button");
        SDL_Quit();
    }
    SDL_QueryTexture(inactiveTexture, NULL, NULL, &this->w, &this->h);
    this->w *= dpiModifier;
    this->h *= dpiModifier;
}

bool Button::handleEvent(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (withinRectangle(x * dpiModifier, y * dpiModifier)) {
            clicked = true;
        }
    } else if (e->type == SDL_MOUSEBUTTONUP && clicked) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (withinRectangle(x * dpiModifier, y * dpiModifier)) {
            clicked = false;
            if (eventHandler != nullptr) {
                return eventHandler(this, e);
            }
        }
    } else if (e->type == SDL_MOUSEMOTION && clicked) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (!withinRectangle(x, y)) {
            clicked = false;
        }
    }


    return false;
}

void Button::cleanup() {
    SDL_DestroyTexture(activeTexture);
    SDL_DestroyTexture(inactiveTexture);
}

void Button::render(bool forceRedraw) {
    if (clicked) {
        renderTexture(activeTexture, getRenderer(), x, y);
    } else {
        renderTexture(inactiveTexture, getRenderer(), x, y);
    }
}
