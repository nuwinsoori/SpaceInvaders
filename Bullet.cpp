#include "Headers/Bullet.h"
#include "Headers/Global.h"
#include <iostream>

Bullet::Bullet(float startX, float startY, float velocity,
               const sf::Texture &texture, bool rotate)
    : velocity(velocity) { // Store the texture reference
  setPosition(startX, startY);
  sprite.setTexture(texture); // Set the texture

  if (rotate) {
    sprite.rotate(180);
  }
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
