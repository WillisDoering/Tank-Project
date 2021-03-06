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

            if (status.game_x + x >= 0 && status.game_y + y >= 0 &&
                    status.game_x + x < map.width && status.game_y + y < map.height &&
                    distVect.at(status.game_x + x + (status.game_y + y) * map.width) 
                    >= 0 && 
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
    attributes tank;
    int points;
    int difference;

    hm.setRadar(baseStats.tankRadar);
    radar = baseStats.tankRange;
    tank.tankAP = pointsAvailable;
    tank.tankDamage = 0;
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
    hostiles.resize(0);
    find_hostiles(map, status.game_x, status.game_y);

    if (obsMap.empty())
    {
        obsMap.resize(map.obstacleMap.size());
        std::fill(obsMap.begin(), obsMap.end(), 0);
    }

    for (int i = 0; i < map.obstacleMap.size(); ++i)
    {
        if (map.obstacleMap[i])
            obsMap[i] = map.obstacleMap[i];
    }


    if(!hm.getMap().size())
        hm.newMap(map, status);
    hm.update(map, status);

    if(!hostiles.size())
    {
        cout << "Wandering\n";
        target = hm.whereTo();
        if (target == std::pair<int,int> (status.game_x, status.game_y))
        {
            hm.newMap(map,status);
            target = hm.whereTo();
            while (map.obstacleMap[target.first+target.second*map.width] == 'R'
                    || map.obstacleMap[target.first + target.second*map.width])
            {
                ++target.first;
                if (target.first == map.width)
                {
                    target.first = 0;
                    ++target.second;
                    if (target.second == map.height)
                        target.second=0;
                }
            }
        }
        cout <<target.first << ' ' << target.second << '\n';
        wf.genMap(map, obsMap, target.first, target.second);
        for (int i = 0; i < map.height; ++i)
        for (int j = 0; j < map.width; ++j)
        {
            if (j == 0)
                cout << '\n';
            cout << setw(4) << wf.waveMap[j + i*map.width];
        }

        cout << "\n\n";
        return 1;
    }
    else
    {
        cout <<"Enemy Sighted\n\n";
        int min_dist = 0xFFFF;
        pair<int, int> min_loc(0, 0);
        int x,y;

        wf.genMap(map, obsMap, status.game_x, status.game_y);

        for (auto enemies : hostiles)
        {
            if (wf.waveMap[enemies.first + enemies.second*map.width] < min_dist)
            {
                x = enemies.first;
                y = enemies.second;
                min_dist = wf.waveMap[enemies.first + enemies.second*map.width];
            }
        }
        min_dist = 0xFFFF;

        cout << x << ' ' << y << '\n';


        for (int j = y-radar; j < y + radar; ++j)
        {
            for (int i = x - radar; i < x + radar; ++i)
            {
                if (i >= 0 && j >= 0 && i < map.width && j < map.height &&
                        wf.waveMap[i+j*map.width] < min_dist && wf.waveMap[i+j*map.width] >= 0)
                {
                    bool beThereRock = false;

                    if(abs(i - x) == abs(j - y))
                    {

                        for (std::pair<int,int> loc(x, y); loc != std::pair<int,int> (i,j); 
                                loc.first+= (i > x) ? 1 : -1 , loc.second += (j > y) ? 1 : -1)
                        {
                            if (map.obstacleMap[loc.first + loc.second*map.width] == 'R')
                                beThereRock = true;
                        }
                    }
                    else if (x - i == 0)
                    {
                        for (int ty = j; ty != y; ty += (y > j) ? 1 : -1)
                            if (map.obstacleMap[x + ty*map.width] == 'R')
                                beThereRock = true;
                    }
                    else if (y - j == 0)
                    {
                        for (int tx = i; tx != x; tx += (x > i) ? 1 : -1)
                            if (map.obstacleMap[tx + y*map.width] == 'R')
                                beThereRock = true;
                    }
                    else
                        beThereRock = true;
                    if (!beThereRock)
                    {
                        min_dist = wf.waveMap[i + j * map.width];
                        min_loc = pair<int, int>(i, j);
                    }
                }
            }
        }
        if (min_dist == 0xFFFF)
        {
            cout <<"ERROR\n\n";
        }

        if (min_dist == 0 && status.ap > 1)
        {
            cout << "MURDER TIME\n\n";
            get_danger(status);
            return 2;
        }
        else if (status.ap > 1)
        {
            cout << "MOVING INTO POSTION\n\n";
            wf.genMap(map, obsMap, min_loc.first, min_loc.second);
            return 1;
        }
        else
        {
            cout << x << ' ' << y << "\n\n";
            for (int i = status.game_x - 1; i < status.game_x + 2; ++i)
            {
                for (int j = status.game_y - 1; j < status.game_y + 2; ++j)
                {
                    if (i-x && j-y && abs(i-x) != abs(j-y)) 
                    {
                        cout << i-x << ' ' << j-y << "\n\n";
                        wf.genMap(map, obsMap, i, j);
                        return 1;
                    }
                }
            }
        }

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
        if (map.map[i] && map.map[i] != id && map.map[i] != -id)
        {

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
