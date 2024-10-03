#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>

class Player : public Entity {
protected:
  unsigned int lives;
  unsigned int playerSpeed;
  unsigned int score;
  unsigned int fireRate;
  bool shield;
  bool triple;
  bool rapid;

public:
  void moveLeft();
  void moveRight();
  void shoot() override;
  unsigned int loseLife();
  bool isAlive();
  unsigned int setSpeed(float newSpeed);
  bool getShieldActive();
  bool getTripleActive();
  bool getRapidActive();
  void setShieldActive();
  void setTripleActive();
  void setRapidActive();
};

#endif
