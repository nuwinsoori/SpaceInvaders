#ifndef ENTITY_H 
#define ENTITY_H

#include <SFML/System/Vector2.hpp>
#include<iostream> 

using namespace std; 

class Entity {
    protected:
        sf::Vector2f position; 
        unsigned int health; 
        float width; 
        float height; 
        bool alive; 
        string colour; 
    public:
        float getDimensions();
        bool checkCollision();
        virtual void shoot(); 
};

#endif