#include "Headers/Player.h"
#include "Headers/Enemy.h"
#include <SFML/Graphics.hpp>

int main() {
  //define dimentions
  float screenWidth = 1200.0f;
  float screenHeight = 800.0f;

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");
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

    // player2 movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player.moveLeft(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player.moveRight(deltaTime);
    }

    //movement ofr enemy
    enemy.move(deltaTime, 50.0f, screenWidth); 

    window.clear();
    player.draw(window);
    enemy.draw(window);
    window.display();
  }

  return 0;
}
