#include "Enemy.h"
#include "Global.h"
#include "Menu.h"
#include "Player.h"
#include "SpecialEnemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

enum state { MENU, PLAYING, LEADERBOARD, GAMEOVER, ENDGAME };

int menu(sf::RenderWindow &window) {
  window.clear();
  Menu menu;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      menu.moveUp();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      menu.moveDown();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      switch (menu.getPressedText()) {
      case 0:
        return ENDGAME; // Start the game
      case 1:
        return LEADERBOARD;
      }
    }

    // drawing
    window.clear();
    menu.draw(window);
    window.display();
  }

  return -1; // Default return if window is closed
}

// TODO:: make return GAMEOVER when player dies to transition gameOver screen.
void play(sf::RenderWindow &window) {
  window.clear();
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
}

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Space Invaders");
  window.setFramerateLimit(120);

  int gameState = menu(window); // Start at the menu state

  while (1) {
    if (gameState == MENU) {
      menu(window);
    }
    if (gameState == PLAYING) {
      play(window);
    }
    if (gameState == LEADERBOARD) {
      // leaderboard
    }
    if (gameState == GAMEOVER) {
      // leaderboard
    }
    if (gameState == ENDGAME) {
      break;
      // leaderboard
    }
  }
  // if left loop game is over
  window.close();
}
