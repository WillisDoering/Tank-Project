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
#include <iomanip>
#include <utility>
#include <algorithm>
#include "WaveFront.h"
#include "HeatMap.h"
using namespace std;


class Archangel : public Actor
{
public:

    Archangel();
    ~Archangel();
    
    std::vector<int> obsMap;
    virtual direction move(MapData map, PositionData status);
    virtual direction attack(MapData map, PositionData status);
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
    virtual int spendAP(MapData map, PositionData status);

private:

    int radar;                          /*!< Radar range */
    vector<pair<int, int>> hostiles;    /*!< Location of all visible hostiles in play */
    vector<int> firing_arc;             /*!< All hostiles within line-of-fire */
    HeatMap hm;                         /*!< HeatMap used for movement */
    WaveFront wf;                       /*!< WaveFront used for movement */
    pair<int, int> target;              /*!< Selected target to move towards */
    int id;

    void find_hostiles(const MapData & map, int x, int y);
    void get_danger(PositionData status);

};

#endif
