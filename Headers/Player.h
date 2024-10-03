#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <iostream>

class Player : public Entity {
protected:
  unsigned int lives;
  unsigned int playerSpeed;
  unsigned int score;
  float fireRate;
  bool shield;
  bool triple;
  bool rapid;

public:
  Player();
  void moveLeft(sf::Time deltaTime);
  void moveRight(sf::Time deltaTime);
  void shoot() override;
  void loseLife();
  bool isAlive();
  void setSpeed(float newSpeed);
  bool getShieldActive();
  bool getTripleActive();
  bool getRapidActive();
  void setShieldActive();
  void setTripleActive();
  void setRapidActive();
};

#endif
