//
//  Button.hpp
//  CityState
//
//  Created by Harry Culpan on 7/7/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <iostream>

#include "Component.hpp"

class Button : public Component {
    bool clicked = false;
    SDL_Texture *activeTexture;
    SDL_Texture *inactiveTexture;
    
public:
    Button(Window *parent, int x, int y, std::string textureFile, EventHandlerFunc eventHandler);
    
    virtual void cleanup();
    virtual void render(bool forceRedraw);
    virtual bool handleEvent(SDL_Event *e);
};

#endif /* Button_hpp */
