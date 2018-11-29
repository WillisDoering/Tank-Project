#include <vector>
#include "src/MapData.h"
#include "src/PositionData.h"
#include <cmath>

class HeatMap
{
    std::vector<int> hmap;
    int radar;
public:
    void newMap(const MapData & map, const PositionData & status);
    void setRadar(int radar);
    const std::vector<int>& getMap();
};
