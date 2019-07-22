//
//  BaseTerrain.cpp
//  CityState
//
//  Created by Harry Culpan on 7/21/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#include "BaseTerrain.hpp"

BaseTerrain::BaseTerrain(TerrainType terrainType, int x, int y) {
    this->m_terrainType = terrainType;
    this->m_x = x;
    this->m_y = y;
}
