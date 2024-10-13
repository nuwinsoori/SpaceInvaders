#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
class Menu {
private:
  const int TEXT_COUNT = 2;
  int selectedItemIndex;
  sf::Font font;
  sf::Text text[2];

public:
  Menu(float x, float y);
  ~Menu();
  void draw(sf::RenderWindow &window);
  void moveUp();
  void moveDown();
  int getPressedText() { return selectedItemIndex; }
};

#endif
