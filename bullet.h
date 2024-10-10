#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <vector>
class Bullet {
private:
  sf::Sprite *sprite;
  sf::Texture *texture;
  sf::Vector2f position;
  float velocity;

public:
  Bullet(sf::Vector2f position, bool rotate);
  bool offScreen();
  sf::FloatRect getDimensions() { return sprite->getGlobalBounds(); }
  ~Bullet();
  void update(sf::Time deltaTime);
  void draw(sf::RenderWindow &window);
};

#endif
