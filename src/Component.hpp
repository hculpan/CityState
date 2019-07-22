//
//  Component.hpp
//  CityState
//
//  Created by Harry Culpan on 7/7/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <iostream>

#include <SDL2/SDL.h>

#include "Window.hpp"

typedef std::function<bool(Window *context, SDL_Event *e)> EventHandlerFunc;

class Component : public Window {
protected:
    EventHandlerFunc eventHandler;
    Component(Window *parent);

public:
    virtual void cleanup() = 0;
    virtual void render(bool forceRedraw) = 0;
    virtual bool handleEvent(SDL_Event *e) = 0;
};

#endif /* Component_hpp */
