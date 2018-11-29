/***************************************************************************//**
 * @file
 * @brief Contains the Archangel tank class
 ****************************************************************************/
#ifndef __ARCHANGEL_H
#define __ARCHANGEL_H

#include "src/Actor.h"
#include "src/direction.h"
#include "src/MapData.h"
#include "src/PositionData.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;


class Archangel : public Actor
{
public:

    Archangel();
    ~Archangel();

    virtual direction move(MapData map, PositionData status);
    virtual direction attack(MapData map, PositionData status);
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
    virtual int spendAP(MapData map, PositionData status);

private:

    vector<int[2]> hostiles; /*!< Location of up to 4 hostiles in play */

    void find_hostiles(MapData map, vector<int[2]> pos);

};

#endif