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
    int minx = 0;
    int miny = 0;
    int minDist = 0xFFFF; //large value
    vector<int> distVect = wf.waveMap;
    for (int x = -1; x < 2; ++x)
    for (int y = -1; y< 2; ++y)
    {
        
        if (status.game_x + x > 0 && status.game_y + y > 0 &&
            status.game_x + x < map.width && status.game_y + y < map.height &&
            distVect.at(status.game_x + x + (status.game_y + y) * map.width) 
                > 0 && 
            distVect.at(status.game_x + x + (status.game_y + y) * map.width) 
                < minDist)
        {
            minDist = distVect.at(status.game_x + x + (status.game_y + y) 
                * map.width);
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
    attributes tank (0,0,0,0,0);
    int points;
    int difference;

    hm.setRadar(baseStats.tankRadar);
    radar = baseStats.tankRadar;
    tank.tankAP = pointsAvailable;
    return tank;



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

    radar = baseStats.tankRadar+tank.tankRadar;

    target.first = -1;
    target.second = -1;

    hm.setRadar(baseStats.tankRadar+tank.tankRadar);
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
    id = status.id;
    //Check for hostiles
    find_hostiles(map, status.game_x, status.game_y);


    if(!hm.getMap().size())
        hm.newMap(map, status);
    hm.update(map, status);

    if(!hostiles.size())
    {

        target = hm.whereTo();
        if (target == std::pair<int,int> (status.game_x, status.game_y))
        {
            hm.newMap(map,status);
            target = hm.whereTo();
        }
        wf.genMap(map, target.first, target.second);
        return 1;
    }
    else
    {
        cout << hostiles.back().first << ' ' << hostiles.back().second << endl;
        int min_dist = 0xFFFF;
        pair<int, int> min_loc(0, 0);

        int x = hostiles[0].first;
        int y = hostiles[0].second;
        wf.genMap(map, status.game_x, status.game_y);

        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                    if ((i || j) && x+i*radar < map.width && y+j*radar < map.height &&
                    x+i*radar >= 0 && y+j*radar >= 0 && wf.waveMap[x+i*radar + (y+j*radar)*map.width] < min_dist)
                {
                    min_dist = wf.waveMap[x+i*radar + (y+j*radar)*map.width];
                    min_loc = pair<int, int>(x+i*radar, y+j*radar);
                }
            }
        }

        if (min_dist == 0);// && status.ap > 1)
        {
            get_danger(status);
            cout << "ATTACK!" << endl;
            return 2;
        }
        //else if( min_dist == 0 && status.ap == 1 )
        {
            get_danger(status);
            switch (firing_arc[0])
            {
                case 1:
                    min_loc.second = status.game_y + 1;
                    break;
                case 2:
                    min_loc.first = status.game_x - 1;
                    min_loc.second = status.game_y + 1;
                    break;
                case 3:
                    min_loc.first = status.game_x -1;
                    break;
                case 4:
                    min_loc.first = status.game_x - 1;
                    min_loc.second = status.game_y - 1;
                    break;
                case 5:
                    min_loc.second = status.game_y - 1;
                    break;
                case 6:
                    min_loc.first = status.game_x + 1;
                    min_loc.second = status.game_y - 1;
                    break;
                case 7:
                    min_loc.first = status.game_x + 1;
                    break;
                case 8:
                    min_loc.first = status.game_x + 1;
                    min_loc.second = status.game_y + 1;
                    break;
            };
        }

        wf.genMap(map, min_loc.first, min_loc.second);
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
void Archangel::find_hostiles(const MapData & map, int x, int y)
{
    //Variables
    int size = map.map.size();
    int currPos = x + y * map.width;

    //Reset hostile vector
    hostiles.resize(0);

    //Add all located tanks
    for (int i = 0; i < size; i++)
    {
        /*cout << map.map[i];
        if (i%map.width == 0) 
            cout << endl;*/
        if (map.map[i] && abs(map.map[i]) != id)
        {
            cout << endl << endl << i << "\n\n";
            cout << map.width << "\n\n";
            pair<int, int> temp(i % map.width, i / map.width);
            hostiles.push_back(temp);
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
        int tankNo = hostiles.size();
        int temp_x;
        int temp_y;

        for(int i=0; i < tankNo; i++)
        {
            temp_x = status.game_x - hostiles[i].first;
            temp_y = status.game_y - hostiles[i].second;

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