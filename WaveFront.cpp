#include "WaveFront.h"

std::vector<int>& WaveFront::genMap(MapData& map, int target_x, int target_y, int d)
{
    int x, y;
    if (d == 0) //set up the vector
    {
        waveMap.resize(map.width * map.height);
        std::fill(waveMap.begin(), waveMap.end(), -1);
    }
    if (target_x < 0 || target_y < 0 || target_x >= map.width || target_y >= map.height)
        return waveMap;
    if (map.obstacleMap[target_x + target_y*map.width] &&( map.obstacleMap[target_x + target_y*map.width] == 'W' || map.obstacleMap[target_x + target_y*map.width] == 'R'))
        return waveMap;

    if (waveMap.at(target_x + target_y*map.width) == -1 || d < waveMap.at(target_x + target_y*map.width))
        waveMap.at(target_x + target_y*map.width) = d;
    else
        return waveMap;
    
    for (x = target_x - 1; x <= target_x + 1; ++x)
    for (y = target_y - 1; y <= target_y + 1; ++y)
    {
        genMap(map, x, y, d+1);
    }
    return waveMap;
}
