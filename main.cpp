#include "Player.h"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(1200, 800), "Space Invaders");
  Player player;
  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    sf::Time deltaTime = clock.restart();

    // player2 movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player.moveLeft(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player.moveRight(deltaTime);
    }
    window.clear();
    player.draw(window);
    window.display();
  }

  return 0;
}
