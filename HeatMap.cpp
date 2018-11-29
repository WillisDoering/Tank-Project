#include "HeatMap.h"
void HeatMap::newMap(const MapData & map, const PositionData & status)
{
    hmap = map.obstacleMap;
    for (int i = 0; i < hmap.size(); ++i)
    {
        if (abs(i % map.width - status.game_x) > radar ||  abs(i / map.width - status.game_y) > radar)
        {

            hmap[i] = 99 - radar + ((abs(i % map.width - status.game_x) - radar >
                              abs(i / map.width - status.game_y) - radar)
                             ? abs(i % map.width - status.game_x) :
                             abs(i / map.width - status.game_y));
        }
    }
    width = map.width;
}
void HeatMap::setRadar(int r)
{
    radar = r;
}
const std::vector<int>& HeatMap::getMap()
{
    return hmap;
}
void HeatMap::update(const MapData & map, const PositionData & status)
{
    for (int i = 0; i < hmap.size(); ++i)
    {
        if ((abs(i % map.width - status.game_x) > radar ||  abs(i / map.width - status.game_y) > radar) && hmap[i] != 0)
        {

            hmap[i] = 99 - radar + ((abs(i % map.width - status.game_x) - radar >
                              abs(i / map.width - status.game_y) - radar)
                             ? abs(i % map.width - status.game_x) :
                             abs(i / map.width - status.game_y));
        }
        else
            hmap[i] = 0;
    }
}
std::pair<int, int> HeatMap::whereTo()
{
    int maxDist = 0;
    int maxIndex = 0;
    for (int i=0; i < hmap.size(); ++i)
    {
        if (hmap[i] > maxDist)
        {
            maxDist = hmap[i];
            maxIndex = i;
        }
    }
    return std::pair<int,int>(maxIndex % width, maxIndex / width);
}
