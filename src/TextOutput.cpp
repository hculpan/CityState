//
//  TextOutput.cpp
//  CityState
//
//  Created by Harry Culpan on 7/8/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#include "TextOutput.hpp"

#include "Game.hpp"
#include "FontManager.hpp"

TextOutput::TextOutput(Window *parent) : Component(parent) {
    this->foregroundColor = { 255, 255, 255, 255 };
}

TextOutput::TextOutput(Window *parent, int x, int y) : TextOutput(parent) {
    this->x = x;
    this->y = y;
}

TextOutput::TextOutput(Window *parent, int x, int y, int fontSize) : TextOutput(parent, x, y) {
    this->fontSize = fontSize;
}

TextOutput::TextOutput(Window *parent, int x, int y, int fontSize, std::string text) : TextOutput(parent, x, y, fontSize) {
    setText(text);
}

void TextOutput::cleanup() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void TextOutput::render(bool forceRedraw) {
    if (forceRedraw) {
        cleanup();
        setText(text);
    }
    
    if (texture) {
        renderTexture(texture, getRenderer(), x, y);
    }
}

bool TextOutput::handleEvent(SDL_Event *e) {
    return false;
}

void TextOutput::setText(std::string text) {
    this->text = text;
    //We'll render the string "TTF fonts are cool!" in white
    //Color is in RGBA format
    texture = renderText(text, fontManager->getFont(FontManager::SOURCESANSPRO_BOLD, fontSize), foregroundColor, getRenderer());
    if (texture == nullptr){
        // cleanup(renderer, window);
        logSDLError("RenderText:textOutput");
        SDL_Quit();
    }
    //Get the texture w/h so we can center it in the screen
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}
