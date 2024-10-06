#include "Headers/Bullet.h"
#include "Headers/Global.h"
#include <iostream>

Bullet::Bullet(float startX, float startY, float velocity)
    : velocity(velocity) {
  setPosition(startX, startY);
  if (!texture.loadFromFile("./Sprites/bullet.png")) {
    std::cout << "Error loading bullet texture!" << std::endl;
  }
  sprite.setTexture(texture);
}

void Bullet::update(sf::Time deltaTime) {
  // Move the bullet along y-axis
  sprite.move(0, velocity * deltaTime.asSeconds());
}

bool Bullet::isOffScreen() {
  // Check if the bullet is outside the screen bounds (above or below)
  sf::FloatRect bulletBounds = sprite.getGlobalBounds();
  return (bulletBounds.top + bulletBounds.height < 0 ||
          bulletBounds.top > SCREEN_HEIGHT);
}
