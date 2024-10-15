#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include <string>
class Menu {
private:
  const int TEXT_COUNT = 2;
  int selectedItemIndex;
  sf::Font font;
  sf::Text text[4];
  std::string previousScore;
  std::string highScore;

public:
  Menu();
  ~Menu();
  void draw(sf::RenderWindow &window);
  void moveUp();
  void moveDown();
  int getPressedText() { return selectedItemIndex; }
};

#endif
