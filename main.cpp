#include "Headers/Enemy.h"
#include "Headers/GameManager.h"
#include "Headers/Global.h"
#include "Headers/Player.h"
#include <SFML/Graphics.hpp>

int main() {
  // rendering window
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                          "Space Invaders");
  window.setFramerateLimit(FRAME_RATE);
  Player player;
  GameManager gameManager;
  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    sf::Time deltaTime = clock.restart();

    // update everything (player, enemy, bullets)
    gameManager.update(deltaTime);

    // drawing
    window.clear();
    gameManager.draw(window);
    window.display();
  }

  return 0;
}
