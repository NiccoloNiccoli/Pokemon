//
// Created by Niccolò Niccoli on 19/06/2020.
//

#ifndef POKEMON_COLLISIONMAP_H
#define POKEMON_COLLISIONMAP_H
#include "Trainer.h"
#include <SFML/Graphics.hpp>

class CollisionMap {
public:
    void load(const std::string &collisionMapName);
    void checkCollisions(Trainer& player,  const int screenWidth, const int screenHeight, sf::Vector2f position);
    std::vector<int> collTiles;



private:

};


#endif //POKEMON_COLLISIONMAP_H
