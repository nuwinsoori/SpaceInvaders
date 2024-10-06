#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

class Player : public Entity {
protected:
  int lives;
  unsigned int playerSpeed;
  unsigned int score;
  float fireRate;
  bool shield;
  bool triple;
  bool rapid;
  sf::Texture texture;

public:
  Player();
  void update(sf::Time deltaTime);
  void moveLeft(sf::Time deltaTime);
  void moveRight(sf::Time deltaTime);
  void shoot() override;
  void loseLife();
  void updateSprite();
  bool isAlive();
  void setSpeed(float newSpeed);
  float getTop();
  bool getShieldActive();
  bool getTripleActive();
  bool getRapidActive();
  void setShieldActive();
  void setTripleActive();
  void setRapidActive();
};

#endif
