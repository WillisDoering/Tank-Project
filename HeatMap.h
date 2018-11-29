#include <vector>
#include "src/MapData.h"
#include "src/PositionData.h"
#include <cmath>
#include <utility>

class HeatMap
{
    std::vector<int> hmap;
    int radar;
    int width;
public:
    void newMap(const MapData & map, const PositionData & status);
    void setRadar(int radar);
    const std::vector<int>& getMap();
    void update(const MapData & map, const PositionData & status);

    std::pair<int, int> whereTo();
};
