//
//  FontManager.cpp
//  CityState
//
//  Created by Harry Culpan on 7/8/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#include "FontManager.hpp"

#include "Game.hpp"

#include <iostream>

FontManager *fontManager = new FontManager();

void FontManager::initialize() {
    // add font file names
    fontFileNames.push_back("SourceSansPro-Regular.otf");
    fontFileNames.push_back("SourceSansPro-Bold.otf");
    
    // add empty font size maps
    for (int i = 0; i < fontFileNames.size(); i++) {
        fontFamiliesArray.push_back(new FontMap());
    }
}

TTF_Font *FontManager::getFont(int fontFamily, int fontSize) {
    TTF_Font *result = NULL;
    if (fontFamily < 0 || fontFamily >= fontFamiliesArray.size()) {
        return NULL;
    }
    FontMap *fontMap = fontFamiliesArray[fontFamily];
    auto f = fontMap->find(fontSize);
    if (f == fontMap->end()) {
        std::string resPath = game->resourcePath + fontFileNames[fontFamily];
        TTF_Font *font = TTF_OpenFont(resPath.c_str(), fontSize);
        if (font == nullptr){
            throw "TTF_OpenFont:getFont";
        }
        (*fontMap)[fontSize] = font;
        result = font;
    } else {
        result = f->second;
    }
    
    return result;
}

