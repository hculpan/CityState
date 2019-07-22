//
//  TextOutput.hpp
//  CityState
//
//  Created by Harry Culpan on 7/8/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#ifndef TextOutput_hpp
#define TextOutput_hpp

#include <string>

#include <SDL2/SDL.h>

#include "Component.hpp"

class TextOutput : public Component {
private:
    std::string text;
    SDL_Texture *texture;
    int fontSize = 14;
    SDL_Color foregroundColor;
    
public:
    TextOutput(Window *parent);
    TextOutput(Window *parent, int x, int y);
    TextOutput(Window *parent, int x, int y, int fontSize);
    TextOutput(Window *parent, int x, int y, int fontSize, std::string text);
    
    virtual void cleanup();
    virtual void render(bool forceRedraw);
    virtual bool handleEvent(SDL_Event *e);
    
    void setText(std::string text);
    std::string getText() const { return text; }
    
    void setFontSize(int fontSize) { this->fontSize = fontSize; }
    int getFontSize() const { return fontSize; }
    
    void setForegroundColor(SDL_Color color) { this->foregroundColor = color; }
    SDL_Color getForegroundColor() const { return this->foregroundColor; }
};

#endif /* TextOutput_hpp */
