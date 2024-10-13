#include "Menu.h"
#include "Global.h"
#include <iostream>

Menu::Menu(float x, float y) {
  if (!font.loadFromFile("./pixelFont.ttf")) {
    std::cout << "ERROR: Loading font" << std::endl;
  }

  text[0].setFont(font);
  text[0].setFillColor(sf::Color::Red);
  text[0].setString("Play");
  text[0].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  text[1].setFont(font);
  text[1].setFillColor(sf::Color::White);
  text[1].setString("Leaderboard");
  text[1].setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 100);

  selectedItemIndex = 0;
}
Menu::~Menu() {}
void Menu::draw(sf::RenderWindow &window) {
  for (int i = 0; i < 2; i++) {
    window.draw(text[i]);
  }
}

void Menu::moveUp() {
  if (selectedItemIndex - 1 >= 0) {
    text[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex--;
    text[selectedItemIndex].setFillColor(sf::Color::Red);
  }
}
void Menu::moveDown() {
  if (selectedItemIndex + 1 < TEXT_COUNT) {
    text[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex++;
    text[selectedItemIndex].setFillColor(sf::Color::Red);
  }
}
