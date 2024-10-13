#include "Enemy.h"
#include "Global.h"
#include "Menu.h"
#include "Player.h"
#include "SpecialEnemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

enum state { MENU, PLAYING, LEADERBOARD, GAMEOVER, ENDGAME };
int gameState = MENU;

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
        return PLAYING; // Start the game
      case 1:
        return ENDGAME;
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

// void GameOver(sf::RenderWindow &window) {
//   window.clear();
//   sf::Text backButton;
//   sf::Font font;
//   if (!font.loadFromFile("./pixelFont.ttf")) {
//     std::cout << "Failed to load font." << std::endl;
//     gameState = ENDGAME;
//     return;
//   }
//   backButton.setFont(font);
//   backButton.setString("BACK");
//   backButton.setFillColor(sf::Color::Red);
//   backButton.setPosition(SCREEN_WIDTH / 2, 750);
//
//   while (window.isOpen()) {
//     sf::Event event;
//     while (window.pollEvent(event)) {
//       if (event.type == sf::Event::Closed)
//         window.close();
//     }
//
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
//       gameState = MENU;
//       return;
//     }
//
//     // drawing
//     window.clear();
//     window.draw(backButton);
//     window.display();
//   }
//
//   gameState = ENDGAME; // Ensure the function returns a value
//   return;
// }

int Leaderboard(sf::RenderWindow &window) {
  window.clear();
  sf::Text backButton;
  sf::Font font;
  if (!font.loadFromFile("./pixelFont.ttf")) {
    std::cout << "Failed to load font." << std::endl;
  }
  backButton.setFont(font);
  backButton.setString("BACK");
  backButton.setFillColor(sf::Color::Red);
  backButton.setPosition(SCREEN_WIDTH / 2, 750);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      return MENU;
    }

    // drawing
    window.clear();
    window.draw(backButton);
    window.display();
  }
  return MENU;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Space Invaders");
  window.setFramerateLimit(120);

  gameState = menu(window); // Start at the menu state

  if (gameState == MENU) {
    menu(window);
  }
  if (gameState == PLAYING) {
    play(window);
  }
  if (gameState == LEADERBOARD) {
    Leaderboard(window);
  }
  if (gameState == GAMEOVER) {
    window.close();
  }
  if (gameState == ENDGAME) {
    // leaderboard
  }
  // if left loop game is over
  // window.close();
}
