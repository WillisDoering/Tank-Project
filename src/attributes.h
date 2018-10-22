#ifndef __ATTRIBUTES_
#define __ATTRIBUTES_

struct attributes
{
    int tankHealth;
    int tankDamage;
    int tankRange;
    int tankShots;

    attributes( int tH, int tD, int tR, int tS ) : tankHealth(tH), 
    tankDamage(tD), tankRange(tR), tankShots(tS) {}
    
    attributes(): tankHealth(0), tankDamage(0), tankRange(0), tankShots(0){}

};

#endif
