#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <iostream>

class PowerUp {
protected:
  sf::Texture *texture;
  sf::Sprite *sprite;
  sf::IntRect healthPower, tripleShoot, rapidShoot;
  enum power { HEALTH, TRIPLE, RAPID };
  int rolledPowerup;

public:
  PowerUp();
  PowerUp(sf::Vector2f enemyPosition);
  void hide();
  void draw(sf::RenderWindow &window);
  void move(sf::Time deltaTime, sf::RenderWindow &window);
  bool inBounds(sf::RenderWindow *window);
  ~PowerUp();
};

#endif
