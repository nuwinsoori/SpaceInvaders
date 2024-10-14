#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <iostream>


class PowerUp {
    protected: 
        sf::Sprite* sprite;
        sf::Texture* texture; 
        bool isPoweredUp; 
        bool powerUpActivated; 
        char name; 
        int time; 
        float speed; 
        

    public:
        PowerUp();
        PowerUp(char classType, sf::Vector2f enemyPosition);
        void hide();
        void draw(sf::RenderWindow *window);
        void update();
        bool checkOutOfBounds(sf::RenderWindow *window);
        ~PowerUp();
        

};


#endif