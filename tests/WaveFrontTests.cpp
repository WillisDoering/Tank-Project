#include "catch.hpp"
#include "../WaveFront.h"
#include "../src/MapData.h"
#include <vector>

TEST_CASE("WaveFrontMap works on an open field")
{
    MapData map(3,3);
    std::vector<int> correct = { 2, 2, 2,
                                 2, 1, 1, 
                                 2, 1, 0 };
    std::vector<int> actual;
    WaveFront wav;
    REQUIRE( wav.genMap(map, 2, 2)  == correct);
}
TEST_CASE("WaveFrontMap works when obstacles are present")
{
    MapData map(3,3);
    map.obstacleMap.at(4) = true;
    map.obstacleMap.at(5) = true;
    std::vector<int> correct = { 3, 3, 4 ,
                                 2, -1, -1, 
                                 2, 1, 0 };
    std::vector<int> actual;
    WaveFront wav;;
    REQUIRE( wav.genMap(map, 2, 2) == correct);
}
