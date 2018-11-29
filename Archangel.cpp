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
}

attributes Archangel::setAttribute(int pointsAvailable)
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
    //Variables
    int hostiles[4][2];
    return 1;
    
}



/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Finds the positions of all the tanks on the map and puts them into a 
 * 2D array.
 * 
 * @param[in]   map - Current map information
 * @param[out]   pos - 2D array of tanks
 *
 ****************************************************************************/
void Archangel::find_hostiles(MapData map, int **pos)
{
    //Variables
    int size = map.width * map.height;
    int x, y;

    //
    for (int i = 0; i < size; i++)
    {
        if (map.map[i])
        {
            hostiles[map.map[i]-1][x] = size % map.width;
            hostiles[map.map[i]-1][x] = floor(size / map.height);
        }
    }
}




extern "C" Actor * maker() {return new Archangel;}
