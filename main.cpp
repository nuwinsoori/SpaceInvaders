#include "Enemy.h"
#include "Player.h"
#include "SpecialEnemy.h"
#include <SFML/Graphics.hpp>
int main() {
  // rendering window
  sf::RenderWindow window(sf::VideoMode(1200, 800), "Space Invaders");
  window.setFramerateLimit(120);
  Player player;
  Enemy enemy;
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    sf::Time deltaTime = clock.restart();
    player.move(deltaTime);
    player.shoot();
    enemy.move(deltaTime);
    enemy.shoot();
    // drawing
    window.clear();
    player.draw(window);
    enemy.drawAll(window);
    window.display();
  }

  return 0;
}
