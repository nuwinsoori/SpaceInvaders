#include "Enemy.h"
#include "Global.h"
#include "Player.h"
#include "SpecialEnemy.h"
#include <SFML/Graphics.hpp>
int main() {
  // rendering window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Space Invaders");
  window.setFramerateLimit(120);
  Player player;
  Enemy enemy;
  SpecialEnemy specialenemy;
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
    specialenemy.move(deltaTime, window);
    player.collision(enemy);
    enemy.shoot();
    player.hit(enemy);
    // drawing
    window.clear();
    player.draw(window);
    enemy.draw(window);
    specialenemy.draw(window);
    window.display();
  }

  return 0;
}
