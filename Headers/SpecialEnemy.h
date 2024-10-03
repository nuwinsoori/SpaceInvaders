#ifndef SPECIALENEMY_H
#define SPECIALENEMY_H

#include "Enemy.h"

class SpecialEnemy : public Enemy {
protected:
  float EnemySpeed;
  int directon;
  float descendAmount;
  unsigned int pointValue;

public:
  void move();
  void shoot() override;
  void dropPowerUp();
};

#endif
