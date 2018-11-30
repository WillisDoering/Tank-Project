#include <vector>
#include "src/MapData.h"
#include "src/direction.h"

class WaveFront
{    
public:
    std::vector<int> waveMap;
    std::vector<int>& genMap(MapData& map, std::vector<int> &, int target_x, int target_y, int d=0);
};
