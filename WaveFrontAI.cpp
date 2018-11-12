#include "WaveFrontAI.h"

/**
 * calculates a move, and returns the data describing its move
 * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
 */
direction WaveFrontAI::move(MapData map, PositionData status)
{
    std::vector<int> distVect;
    std::vector<int> alternateDist;
    for (int i = 0; i < map.width*map.height; ++i)
    {
        if (map.map.at(i) > 0 && map.map.at(i) != status.id)
        {
            if (distVect.size() == map.width * map.height)
            {
                waveFront(alternateDist, map, i % map.width, i / map.width);
            }
            else
            {
                waveFront(distVect, map, i % map.width, i / map.width);
                alternateDist = distVect;
            }
            if (alternateDist.at(i) < distVect.at(i))
                distVect.at(i) = alternateDist.at(i);
        }
    }
    if (distVect.size() != map.width*map.height) //no enemies found
        waveFront(distVect, map, 10, 4);


    int minx = 0;
    int miny = 0;
    int minDist = 0xFFFF; //large value
    for (int x = -1; x < 2; ++x)
    for (int y = -1; y< 2; ++y)
    {
        
        if (status.game_x + x > 0 && status.game_y + y > 0 &&
            status.game_x + x < map.width && status.game_y + y < map.height &&
            distVect.at(status.game_x + x + (status.game_y + y) * map.width) > 0 && 
            distVect.at(status.game_x + x + (status.game_y + y) * map.width) < minDist)
        {
            minDist = distVect.at(status.game_x + x + (status.game_y + y) * map.width);
            minx = x;
            miny = y;
        }
        
    }

    
    if (minx < 0)
    {
        return (miny > 0) ? DOWNLEFT : (miny < 0) ? UPLEFT : LEFT;
    }
    if (minx > 0)
    {
        return (miny > 0) ? DOWNRIGHT : (miny < 0) ? UPRIGHT : RIGHT;
    }

    return (miny > 0) ? DOWN : (miny < 0) ? UP : STAY;
}

/**
 * calculates an attack and returns the data describing its attack
 * @return Attack data the desired attack to be made, if possible the gamefield will do the move
 */
direction WaveFrontAI::attack(MapData map, PositionData status)
{
    direction ret = STAY;
    int min_dist = 0xFFFF;
    for (int x = 0; x < map.width; ++x)
    {
        for (int y = 0; y < map.height; ++y)
        {
            //If an enemy is encountered closer than previously encountered
            if ( map.map[x + y*map.width] && //if there is an actor at X, Y
                 map.map[x + y*map.width] != status.id && //And it is not you
                 map.map[x + y*map.width] != -status.id && //And it is not your projectile
                 calcDist(status.game_x, status.game_y, x, y) < min_dist) //And it is the closest one
            {
                if (x == status.game_x || y == status.game_y ||(
                        abs(x - status.game_x) == abs(status.game_y - y)))
                {
                    min_dist = calcDist(status.game_x, status.game_y, x, y);
                    if (status.game_x == x)
                    {
                        ret = (y > status.game_y) ? DOWN : UP;
                    }
                    else if (status.game_y == y)
                    {
                        ret = (x > status.game_x) ? RIGHT : LEFT;
                    }
                    else if (status.game_x > x) //to the upright or downright
                    {
                        ret = (y > status.game_y) ? DOWNLEFT : UPLEFT;
                    }
                    else
                    {
                        ret = (y > status.game_y) ? DOWNRIGHT : UPRIGHT;
                    }
                }
            
            }
        }
    }
    return ret;

}

attributes WaveFrontAI::setAttribute(int pointsAvailable, attributes baseStats)
{
    return attributes (pointsAvailable/2, pointsAvailable - pointsAvailable/2, 0,0,0);
}

int WaveFrontAI::spendAP(MapData map, PositionData status)
{
//1 move, 2 attack, 3 end turn
    return (status.ap > 1) ? 1 : 2;
}

int WaveFrontAI::calcDist(int x1, int y1, int x2, int y2)
{
    return (std::abs(x1 - x2) + std::abs(y1 - y2));
}

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
