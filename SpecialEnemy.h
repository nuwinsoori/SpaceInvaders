#ifndef SPECIALENEMY_H
#define SPECIALENEMY_H

#include"Enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class SpecialEnemy : public Enemy {
    private:
        int SEdirection; 
        unsigned int pointVal;
        sf::Sprite *sprite;
        sf::Texture *texture;
        sf::Clock SEMoveTime;

    public:
        SpecialEnemy();
        void move(sf::Time deltaTime); //, sf::RenderWindow &window
        bool HasReachedTarget(sf::Vector2f target);
        bool checkIfOffScreen();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow &window) override;
        void DropPowerUp();
        void die();
};

#endif