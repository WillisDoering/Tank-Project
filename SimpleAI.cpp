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
    int rand_direction;
    rand_direction = rand() % 5 + 1;
    switch (rand_direction)
    {
        case 1:
            return UP;
        case 2:
            return DOWN;
        case 3:
            return LEFT;
        case 4:
            return RIGHT;
        case 5:
            return STAY;
    }
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
    int ret = (direction) rand() % 4 +1;
    switch (ret)
    {
        case 1:
            return UP;
        case 2:
            return DOWN;
        case 3:
            return LEFT;
        case 4:
            return RIGHT;
    }
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

   return tankAttributes;
}


int SimpleAI::spendAP(MapData map, PositionData status)
{
    return (rand() % 3 +1); 
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
