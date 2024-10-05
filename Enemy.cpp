#include "./Headers/Enemy.h"
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf; 

//constructor defines all varibles.
Enemy::Enemy(){
    setPosition(10.f, 50.f);
    if (!texture.loadFromFile("./Sprites/1163.png")) {
    cout << "Error loading enemy texture." << endl;
    }
    sprite.setTexture(texture);
    sprite.scale(0.25f, 0.25f);
}


//function that make enemies move
void Enemy::move(sf::Time deltaTime, float EnemySpeed, float screenWidth){
    sprite.move(EnemySpeed * deltaTime.asSeconds(), 0);

    // sf::FloatRect boundary = getDimensions();
    if(sprite.getPosition().x > screenWidth){
        sprite.setPosition(0, sprite.getPosition().y);
    }
}

//functiion that makes enemies go down once move all way left or right.
void Enemy::descent(){

}

//function that makes the enemies change direction. 
void Enemy::changeDirection(){

}

//function that checks if enemies have reached end of screen. 
bool Enemy::reachedEndOfScreen(){

}

