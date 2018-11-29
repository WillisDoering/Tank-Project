/***************************************************************************//**
 * @file
 * @brief Contains functions for the Archangel class
 ****************************************************************************/
#include "Archangel.h"


/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Constructor for the Archangel class.
 *
 ****************************************************************************/
Archangel::Archangel(){}


/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Destructor for the Archangel class.
 *
 ****************************************************************************/
Archangel::~Archangel(){}


/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Calculates tank movement.
 *
 ****************************************************************************/
direction Archangel::move(MapData map, PositionData status)
{
    //Variables
    int const MAP_SIZE = map.width + map.height;
    direction move = STAY;

    return move;
    
}

direction Archangel::attack(MapData map, PositionData status)
{
    return UP;
}

attributes Archangel::setAttribute(int pointsAvailable, attributes baseStats)
{
    //Variables
    attributes tank;
    int points;

    //Assign points
    while (pointsAvailable)
    {
        //Base number used to decide where points will go
        points = pointsAvailable % 4;

        //Determine where points go
        switch(points)
        {
            case 1:
            case 2:
                tank.tankAP++;
                break;
            case 3:
                tank.tankHealth++;
                break;
            case 0:
                tank.tankShots++;
                break;
        }

        //Decrament and loop
        pointsAvailable--;
    }

    return tank;
}

int Archangel::spendAP(MapData map, PositionData status)
{
    //TEST: find_hostiles
    find_hostiles(map, status.game_x, status.game_y);
    return (hostiles.size() > 0) ? 2 : 3;
}



/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Finds the positions of all the tanks on the map and puts them into a 
 * 2D array.
 * 
 * @param[in]   map - Current map information
 * @param[out]  pos - 2D array of tanks
 *
 ****************************************************************************/
void Archangel::find_hostiles(MapData map, int x, int y)
{
    //Variables
    int size = map.width * map.height;
    int currPos = x + y * map.width;

    //Reset hostile vector
    hostiles.clear();

    //Add all located tanks
    for (int i = 0; i < size; i++)
    {
        if (map.map[i] && i != currPos)
        {
            hostiles.push_back(i % map.width);
            hostiles.push_back(floor(i / map.width));
        }
    }
}



#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new Archangel;
    }
}
#endif