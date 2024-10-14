#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <iostream>

class PowerUp {
protected:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::IntRect healthPower, tripleShoot, rapidShoot;
  int rolledPowerup;

public:
  PowerUp(sf::Vector2f enemyPosition);
  ~PowerUp();
  void hide();
  void draw(sf::RenderWindow &window);
  void move(sf::Time deltaTime);
  bool inBounds();
  sf::FloatRect getDimensions() { return sprite.getGlobalBounds(); }
  int getType();
  sf::Sprite getSprite() const { return sprite; }

  // TODO: DELETE LATER
  float getHeight() { return sprite.getPosition().y; }
};

#endif
