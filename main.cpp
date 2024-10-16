#include "Enemy.h"
#include "Global.h"
#include "Menu.h"
#include "Player.h"
#include "SpecialEnemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

// handling game state
enum state { MENU, PLAYING, GAMEOVER, ENDGAME };
int gameState = MENU;

// draws menu on game window
int menu(sf::RenderWindow &window) {
  window.clear();
  Menu menu;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // move between menu buttons
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      menu.moveUp();
    }

    // move between menu buttons
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      menu.moveDown();
    }

    // handles game state depending on button pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      switch (menu.getPressedText()) {
      case 0:
        return PLAYING; // Start the game
      case 1:
        return ENDGAME; // exits game
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

// handles playing game slate
int play(sf::RenderWindow &window) {
  window.clear();
  // creates instances of player, eney and SE
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

    // where all the functions are called
    sf::Time deltaTime = clock.restart();
    player.update(deltaTime);
    enemy.move(deltaTime);
    specialenemy.spawn(enemy);
    specialenemy.move(deltaTime);
    player.collision(enemy, specialenemy);
    enemy.shoot();
    player.hit(enemy);

    // drawing
    window.clear();
    player.draw(window);
    player.drawPowerUps(window);
    enemy.draw(window);
    specialenemy.draw(window);
    window.display();

    // goes to game over if player is dead
    if (!player.isAlive()) {
      return GAMEOVER;
    }
  }
  return GAMEOVER;
}

// game over state
int GameOver(sf::RenderWindow &window) {
  window.clear();
  sf::Text backButton;
  sf::Font font;
  if (!font.loadFromFile("./pixelFont.ttf")) {
    std::cout << "Failed to load font." << std::endl;
    return ENDGAME;
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

//
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
  // seed rng
  srand(static_cast<unsigned int>(time(NULL)));
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                          "Space Invaders");
  window.setFramerateLimit(120);

  gameState = menu(window); // Start at the menu state

  while (window.isOpen()) {
    if (gameState == MENU) {
      gameState = menu(window);
      continue;
    }
    if (gameState == PLAYING) {
      gameState = play(window);
      continue;
    }
    if (gameState == GAMEOVER) {
      gameState = GameOver(window);
      continue;
    }
    if (gameState == ENDGAME) {
      break;
    }
  }
  // if left loop game is over
  window.close();
}
