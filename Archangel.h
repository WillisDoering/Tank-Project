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
#include "WaveFront.h"
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
    
    int radar;              /*!< Radar range */
    vector<int> hostiles;   /*!< Location of up to 4 hostiles in play */
    vector<int> firing_arc; /*!< All hostiles within line-of-fire */

    void find_hostiles(MapData map, int x, int y);
    void get_danger(PositionData status);

};

#endif