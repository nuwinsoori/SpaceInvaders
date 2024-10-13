#include "Menu.h"
#include "Global.h"
#include <fstream>
#include <iostream>
#include <string>

Menu::Menu() {
  if (!font.loadFromFile("./pixelFont.ttf")) {
    std::cout << "ERROR: Loading font" << std::endl;
  }

  // buttons
  text[0].setFont(font);
  text[0].setFillColor(sf::Color::Red);
  text[0].setString("Play");
  text[0].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150);

  text[1].setFont(font);
  text[1].setFillColor(sf::Color::White);
  text[1].setString("Exit");
  text[1].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);

  selectedItemIndex = 0;

  // handle reading and writing score
  std::ifstream scoreFile;
  scoreFile.open("./scores.txt");

  if (scoreFile.fail()) {
    std::cout << "ERROR: could not open file" << std::endl;
  }
  if (scoreFile.is_open()) {
    std::getline(scoreFile, this->previousScore);
    std::getline(scoreFile, this->highScore);
  }
  scoreFile.close();

  // Leaderboard

  text[2].setFont(font);
  text[2].setFillColor(sf::Color::White);
  text[2].setString("Previous Score: " + previousScore);
  text[2].setPosition((SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) + 40);
  text[2].setScale(0.75f, 0.75f);

  text[3].setFont(font);
  text[3].setFillColor(sf::Color::White);
  text[3].setString("High Score: " + highScore);
  text[3].setPosition((SCREEN_WIDTH / 2) - 55, (SCREEN_HEIGHT / 2) + 80);
  text[3].setScale(0.75f, 0.75f);
}

Menu::~Menu() {}
void Menu::draw(sf::RenderWindow &window) {
  for (int i = 0; i < 4; i++) {
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
