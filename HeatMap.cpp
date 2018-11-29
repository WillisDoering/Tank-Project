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
}
void HeatMap::setRadar(int r)
{
    radar = r;
}
const std::vector<int>& HeatMap::getMap()
{
    return hmap;
}
