#include "SimpleAI.h"
#include <iostream>

SimpleAI::SimpleAI() {}
SimpleAI::~SimpleAI() {}

/**
 * @author David Donahue
 * @par Description:
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return direction to move
 */
direction SimpleAI::move(MapData map, PositionData status)
{
    int min_dist = map.width * map.height + 1;
    direction ret = STAY;
    for (int x = 0; x < map.width; ++x)
    {
        for (int y = 0; y < map.height; ++y)
        {
            //If an enemy is encountered closer than previously encountered
            if ( map.map[x + y*map.width] > 0 &&
                 map.map[x + y*map.width] != status.id &&
                 calcDist(status.game_x, status.game_y, x, y) < min_dist &&
                 calcDist(status.game_x, status.game_y, x, y) > 1)
            {
                min_dist = calcDist(status.game_x, status.game_y, x, y);

                if (std::abs(status.game_x - x) > std::abs(status.game_y - y)) //more horizontal distance
                {
                    if (status.game_x > x)
                    {
                        if(!map.obstacleMap[status.game_x - 1 + status.game_y * map.width]) //check for obstacle
                        {
                            ret = LEFT;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_y > y) ? UP : DOWN; //avoid it up or down
                        }
                    }
                    else
                    {
                        if(!map.obstacleMap[status.game_x + 1 + status.game_y * map.width]) //check for obstacle
                        {
                            ret = RIGHT;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_y > y) ? UP : DOWN; //avoid it up or down
                        }
                    }

                }
                else
                {
                    if (status.game_y > y)
                    {
                        if(!map.obstacleMap[status.game_x + (status.game_y - 1)*map.width]) //check for obstacle
                        {
                            ret = UP;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_x > x) ? LEFT : RIGHT; //avoid it left or right
                        }
                    }
                    else
                    {
                        if(!map.obstacleMap[status.game_x + (status.game_y + 1)*map.width]) //check for obstacle
                        {
                            ret = DOWN;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_x > x) ? LEFT : RIGHT; //avoid it left or right
                        }
                    }
                }
            }
        }
    }
    return ret;
}

/**
 * @author David Donahue
 * @par Description: 
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return Location to attack and whether to attack
 */
direction SimpleAI::attack(MapData map, PositionData status)
{
    direction ret = STAY;
    int min_dist = map.width * map.height + 1; //Guaranteed to be greater than any real distance
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

/**
 * @author David Donahue
 * @par Description:
 * Returns the attributes for the tank
 * @param[in] pointsAvailable - available points for the distribution
 * @return attributes of the tank
 */
attributes SimpleAI::setAttribute(int pointsAvailable)
{
   attributes tankAttributes;

   tankAttributes.tankHealth = 100000000;

   return tankAttributes;
}
/**
 * @author David Donahue
 * @par Description: 
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] x1 - starting point x coordinate
 * @param[in] y1 - starting point y coordinate
 * @param[in] x2 - end point x coordinate
 * @param[in] y2 - end point y coordinate
 * @return distance to the target
 */
int SimpleAI::calcDist(int x1, int y1, int x2, int y2)
{
    return (std::abs(x1 - x2) + std::abs(y1 - y2));
}


int SimpleAI::spendAP(MapData map, PositionData status)
{
    if (move(map, status) == STAY && attack(map,status) != STAY) //If there is nowhere to move, attack
        return 2;
    
    if (attack(map, status) == STAY && move(map,status) != STAY) //If there is nowhere to attack, move
        return 1;

    if (attack(map,status) == STAY && move(map,status) == STAY) //If there is nothing to do, end your turn
        return 3;
    
    return (status.ap > 1) ? 1 : 2;
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new SimpleAI;
    }
}
#endif
