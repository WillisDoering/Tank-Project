#include "WaveFrontAI.h"

/**
 * calculates a move, and returns the data describing its move
 * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
 */
direction WaveFrontAI::move(MapData map, PositionData status) {}

/**
 * calculates an attack and returns the data describing its attack
 * @return Attack data the desired attack to be made, if possible the gamefield will do the move
 */
direction WaveFrontAI::attack(MapData map, PositionData status) {}

attributes WaveFrontAI::setAttribute(int pointsAvailable) {}

int WaveFrontAI::spendAP(MapData map, PositionData status) {}

//generates a wavefront map for pathfinding
void WaveFrontAI::waveFront (std::vector<int> &distVect, MapData map, int tx, int ty, int d)
{
    int x, y;
    if (distVect.size() != map.width * map.height || (d == 0 && distVect.at(tx*ty) != 0)) //set up the vector
    {
        distVect.resize(map.width * map.height);
        std::fill(distVect.begin(), distVect.end(), -1);
        
    }
    if (tx < 0 || ty < 0 || tx >= map.width || ty >= map.height)
        return;
    if (map.obstacleMap[tx + ty*map.width])
        return;

    if (distVect.at(tx + ty*map.width) == -1 || d < distVect.at(tx + ty*map.width))
        distVect.at(tx + ty*map.width) = d;
    else
        return;
    
    for (x = tx - 1; x <= tx + 1; ++x)
    for (y = ty - 1; y <= ty + 1; ++y)
    {
        waveFront(distVect, map, x, y, d+1);
    }
    
}

WaveFrontAI::WaveFrontAI() {}
WaveFrontAI::~WaveFrontAI() {}

extern "C" Actor * maker() {return new WaveFrontAI;}
