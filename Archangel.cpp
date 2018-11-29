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


/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Fires at first target in line-of-fire
 *
 ****************************************************************************/
direction Archangel::attack(MapData map, PositionData status)
{
    switch (firing_arc[0])
    {
        case 1:
            return UP;
        case 2:
            return UPRIGHT;
        case 3:
            return RIGHT;
        case 4:
            return DOWNRIGHT;
        case 5:
            return DOWN;
        case 6:
            return DOWNLEFT;
        case 7:
            return LEFT;
        case 8:
            return UPLEFT;
        default:
            return STAY;
    };
}


/*************************************************************************//**
 * @author William Doering, David Donahue, Mike Theesen, Dillon Roller
 *
 * @par Description:
 * Evens out the range and radar stats if possible and then evenly distributes
 * the special points between the two. If it's not possible, buff damage and
 * AP.
 * 
 * param[in]    pointsAvailable - Special points available to spend
 * param[in]    baseStats - base stats started with
 *
 ****************************************************************************/
attributes Archangel::setAttribute(int pointsAvailable, attributes baseStats)
{
    attributes tank;
    int points;
    int difference;

    if(baseStats.tankRange != baseStats.tankRadar && pointsAvailable)
    {
        difference = baseStats.tankRange - baseStats.tankRadar;
        if(abs(difference) <= pointsAvailable)
        {
            if(difference < 0)
                tank.tankRange += abs(difference);
            else
                tank.tankRadar += abs(difference);
            pointsAvailable -= abs(difference);
        }
        else
        {
            tank.tankDamage = pointsAvailable / 2;
            pointsAvailable -= (pointsAvailable / 2);
            tank.tankAP = pointsAvailable;
        }
    }

    while(pointsAvailable > 1)
    {
        tank.tankRange++;
        tank.tankRadar++;
        pointsAvailable -= 2;
    }

    if(pointsAvailable) tank.tankAP++;

    radar = baseStats.tankRadar;

    target.first = -1;
    target.second = -1;

    return tank;
}


/*************************************************************************//**
 * @author William Doering, David Donahue, Mike Theesen, Dillon Roller
 *
 * @par Description:
 *
 *
 ****************************************************************************/
int Archangel::spendAP(MapData map, PositionData status)
{
    //Check for hostiles
    find_hostiles(map, status.game_x, status.game_y);

    if(!hm.getMap().size())
        hm.newMap(map, status);

    hm.update(map, status);

    if(!hostiles.size())
    {
        if(target.first == -1 && target.second == -1)
            target = hm.whereTo();
        wf.genMap(map, target.first, target.second);
        return 1;
    }
    
    

    return 3;
}


/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Finds the positions of all the tanks on the map and puts them into a 
 * vector.
 * 
 * @param[in]   map - Current map information
 * @param[in]   x - x position of self
 * @param[in]   y - y position of self
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


/*************************************************************************//**
 * @author William Doering
 *
 * @par Description:
 * Finds whether enemy is within line-of-fire. If they are, it pushes the 
 * direction onto the vector of ints. Directions as follows:
 * 1 - UP
 * 2 - UPRIGHT
 * 3 - RIGHT
 * 4 - DOWNRIGHT
 * 5 - DOWN
 * 6 - DOWNLEFT
 * 7 - LEFT
 * 8 - UPLEFT
 * 
 * param[in]    status - tank stats 
 *
 ****************************************************************************/
void Archangel::get_danger(PositionData status)
{
    firing_arc.clear();

    //Check if hostiles are seen
    if (hostiles.size())
    {
        //Variables
        int tankNo = hostiles.size() / 2;
        int temp_x;
        int temp_y;

        for(int i=0; i < tankNo; i++)
        {
            temp_x = status.game_x - hostiles[i*2];
            temp_y = status.game_y - hostiles[(i*2)+1];

            if(!temp_x)
                firing_arc.push_back((temp_y > 0) ? 1 : 5);
            else if(!temp_y)
                firing_arc.push_back((temp_x > 0) ? 7 : 3);
            else if(temp_x == temp_y)
                firing_arc.push_back((temp_x > 0) ? 8 : 4);
            else if(temp_x == temp_y * -1)
                firing_arc.push_back((temp_x > 0) ? 6 : 2);
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