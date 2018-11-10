#include "CamperAI.h"

CamperAI::CamperAI(void)
{
    // Tells the move function that we can go anywhere
}

CamperAI::~CamperAI(void)
{
}

direction CamperAI::move(MapData map, PositionData status)
{
    int x_pos = status.game_x;
    int y_pos = status.game_y;
    int median = map.height / 2;
    int median2 = map.width / 2;

    direction retval = DOWN;
    if((y_pos == 0 && x_pos == 0) ||
       (y_pos == map.height - 1 && x_pos == 0) ||
       (x_pos == map.width - 1 && y_pos == 0) ||
       (x_pos == map.width - 1 && y_pos == map.height - 1))
        retval = STAY;
    else if(y_pos <= median)
        retval = UP;
    else if(y_pos > median)
        retval = DOWN;
    else if(x_pos > median2)
        retval = RIGHT;
    else if(x_pos <= median2)
        retval = LEFT;
    else
        retval == STAY;

    return retval;
}

direction CamperAI::attack(MapData map, PositionData status)
{
    int y_pos = status.game_y;
    int x_pos = status.game_x;
    int hmedian = map.height / 2;
    int wmedian = map.width / 2;
    direction retval;

    if(y_pos >= hmedian && x_pos <= wmedian)
    {
        switch (turn)
        {
        case 1:
            retval = UPRIGHT;
            break;
        case 2:
            retval = RIGHT;
            break;
        default:
            retval = UP;
            break;
        }
    }
    else if(y_pos < hmedian && x_pos <= wmedian)
    {
        switch (turn)
        {
        case 1:
            retval = DOWNRIGHT;
            break;
        case 2:
            retval = RIGHT;
            break;
        default:
            retval = DOWN;
            break;
        }
    }
    else if(y_pos >= hmedian && x_pos > wmedian)
    {
        switch (turn)
        {
        case 1:
            retval = UPLEFT;
            break;
        case 2:
            retval = LEFT;
            break;
        default:
            retval = UP;
            break;
        }
    }
    else if(y_pos < hmedian && x_pos > wmedian)
    {
        switch (turn)
        {
        case 1:
            retval = DOWNLEFT;
            break;
        case 2:
            retval = LEFT;
            break;
        default:
            retval = DOWN;
            break;
        }
    }

    return retval;
}

attributes CamperAI::setAttribute(int pointsAvailable, attributes baseStats)
{
    attributes retval;

    retval.tankHealth = pointsAvailable;

    return retval;
}

int CamperAI::spendAP(MapData map, PositionData status)
{
    if (maxAp == 0)
        maxAp = status.ap;
    if (maxAp == status.ap)
        turn = 0;
    else
        turn++;
    if (move(map, status) != STAY)
        return 1;
    return 2; // Attack
}



#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new CamperAI;
    }
}
#endif
