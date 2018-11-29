#include "catch.hpp"
#include "../HeatMap.h"
#include "../src/MapData.h"
#include "../src/PositionData.h"
#include <vector>

TEST_CASE("HeatMap constructs")
{
    HeatMap hm;
    REQUIRE(sizeof(hm) > 0);
}


TEST_CASE("HeatMap.newMap() generates a heatmap from the current position")
{
    HeatMap hm;
    hm.setRadar(4);
    MapData map(10,10);
    PositionData status(1, 1, 0, 0, 0, 0);
    hm.newMap(map, status);
    std::vector<int> correct = {0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103, 104,
                                0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103, 104,
                                0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103, 104,
                                0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103, 104,
                                0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103, 104,
                                100, 100, 100, 100, 100, 100, 101, 102, 103, 104,
                                101, 101, 101, 101, 101, 101, 101, 102, 103, 104,
                                102, 102, 102, 102, 102, 102, 102, 102, 103, 104,
                                103, 103, 103, 103, 103, 103, 103, 103, 103, 104,
                                104, 104, 104, 104, 104, 104, 104, 104, 104, 104};
                              
    REQUIRE(hm.getMap() == correct);

}

TEST_CASE("HeatMap.update() updates the existing heatmap to reflect newly uncovered locations")
{
    HeatMap hm;
    hm.setRadar(4);
    MapData map(10,10);
    PositionData status(1, 1, 0, 0, 0, 0);
    hm.newMap(map, status);
    status.game_x++;
    hm.update(map, status);
    std::vector<int> correct = {0  , 0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103,
                                0  , 0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103,
                                0  , 0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103,
                                0  , 0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103,
                                0  , 0  , 0  , 0  , 0  , 0  , 100, 101, 102, 103,
                                100, 100, 100, 100, 100, 100, 100, 101, 102, 103,
                                101, 101, 101, 101, 101, 101, 101, 101, 102, 103,
                                102, 102, 102, 102, 102, 102, 102, 102, 102, 103,
                                103, 103, 103, 103, 103, 103, 103, 103, 103, 103,
                                104, 104, 104, 104, 104, 104, 104, 104, 104, 104};
                              
    REQUIRE(hm.getMap() == correct);
}
