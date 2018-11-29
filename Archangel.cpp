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
    vector<int> fire = get_danger(status);
    if (!fire.size()) return STAY;
    switch (fire[0])
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
    radar = baseStats.tankRadar;

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
 * 
 * 
 *
 ****************************************************************************/
vector<int> Archangel::get_danger(PositionData status)
{
    vector<int> tank_dir;
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
                tank_dir.push_back((temp_y > 0) ? 1 : 5);
            else if(!temp_y)
                tank_dir.push_back((temp_x > 0) ? 7 : 3);
            else if(temp_x == temp_y)
                tank_dir.push_back((temp_x > 0) ? 8 : 4);
            else if(temp_x == temp_y * -1)
                tank_dir.push_back((temp_x > 0) ? 6 : 2);
        }
    }

    return tank_dir;
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