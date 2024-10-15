#ifndef SPECIALENEMY_H
#define SPECIALENEMY_H

#include "Enemy.h"
#include "Global.h"
#include "PowerUp.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class SpecialEnemy : public Enemy {
private:
  unsigned int pointVal;
  sf::Sprite sprite;
  sf::Texture texture;
  sf::Clock SEMoveTime;
  bool isActive;
  bool playSound;
  sf::SoundBuffer dieBuffer, activeBuffer;
  sf::Sound dieSound, activeSound;

public:
  SpecialEnemy();
  ~SpecialEnemy();
  void move(sf::Time deltaTime);
  bool HasReachedTarget(sf::Vector2f target, sf::RenderWindow &window);
  void checkIfOffScreen();
  int getSEPoints();
  void update(sf::Time deltaTime);
  void spawn(Enemy &enemy);
  void draw(sf::RenderWindow &window) override;
  PowerUp *DropPowerUp();
  // void die();
  PowerUp *die(bool killed);
  sf::FloatRect getDimensions() { return sprite.getGlobalBounds(); }
  sf::Vector2f dropLocation();
  void goStart();
};

#endif
