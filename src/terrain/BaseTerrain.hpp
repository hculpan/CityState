//
//  BaseTerrain.hpp
//  CityState
//
//  Created by Harry Culpan on 7/21/19.
//  Copyright © 2019 Harry Culpan. All rights reserved.
//

#ifndef BaseTerrain_hpp
#define BaseTerrain_hpp

enum TerrainType {
    Unknown,
    Clear,
    Wood
};

enum ActionTypes {
    GatherFood = 1 << 0,
    GatherWood = 1 << 1
};

class BaseTerrain {
public:
    virtual ActionTypes availableActions() = 0;

    TerrainType terrainType() const { return m_terrainType; }
    
    int x() { return m_x; }
    int y() { return m_y; }
    
protected:
    BaseTerrain(TerrainType terrainType, int x, int y);

    TerrainType m_terrainType;
    
    int m_x;
    int m_y;
};

#endif /* BaseTerrain_hpp */
