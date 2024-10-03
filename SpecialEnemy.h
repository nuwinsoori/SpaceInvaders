#ifndef SPECIALENEMY_H
#define SPECIALENEMY_H

#include "Enemy.h"


class SpecialEnemy : protected Enemy {
    protected:
        float EnemySpeed; 
        int directon; 
        float descendAmount; 
        unsigned int pointValue;
    public:
        override void move(); 
        override void shoot(); 
        void dropPowerUp(); 
};

#endif