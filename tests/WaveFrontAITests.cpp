#include "catch.hpp"
#include "../WaveFrontAI.h"
#include "../src/MapData.h"
#include <vector>

TEST_CASE("WaveFrontAI constructs")
{
    REQUIRE(sizeof(WaveFrontAI) > 0);
}

TEST_CASE("WaveFrontMap works on an open field")
{
    MapData map(3,3);
    std::vector<int> correct = { 2, 2, 2,
                                 2, 1, 1, 
                                 2, 1, 0 };
    std::vector<int> actual;
    WaveFrontAI wav;
    wav.waveFront(actual, map, 2, 2);
    REQUIRE( actual == correct);
}
