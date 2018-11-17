#ifndef __WAVE_FRONT_AI_H
#define __WAVE_FRONT_AI_H

#include "src/Actor.h"
#include "src/direction.h"
#include "src/MapData.h"
#include "src/PositionData.h"
#include <iostream>

class WaveFrontAI : public Actor
{
    int calcDist(int x1, int y1, int x2, int y2);

public:

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(MapData map, PositionData status);

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual direction attack(MapData map, PositionData status);

    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);

    virtual int spendAP(MapData map, PositionData status);

    //generates a wavefront map for pathfinding
    void waveFront (std::vector<int> &distVect, MapData &map, int tx, int ty, int d = 0);

    WaveFrontAI();
    ~WaveFrontAI();
};


#endif
