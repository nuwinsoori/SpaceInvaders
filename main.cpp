#include "Player.h"
#include <SFML/Graphics.hpp>
int main() {
  // rendering window
  sf::RenderWindow window(sf::VideoMode(1200, 800), "Space Invaders");
  window.setFramerateLimit(120);
  Player player;
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
    // drawing
    window.clear();
    player.draw(window);
    window.display();
  }

  return 0;
}
