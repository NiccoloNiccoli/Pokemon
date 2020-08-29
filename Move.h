//
// Created by Niccolò Niccoli on 23/06/2020.
//

#ifndef POKEMON_MOVE_H
#define POKEMON_MOVE_H


#include <string>
#include "Type.h"
#include "debug.h"
#include "AnimatedSprite.h"

class Move {
public:
    Move();
    explicit Move(const std::string& moveName);
    void draw(sf::RenderWindow& window,int row);

    int getPower() const;

    float getHealingPercentage() const;

    int getNUsage() const;

    void setNUsage(int nUsage);

    const std::string &getName() const;

    const Type &getType() const;

    int getAccuracy() const;

    int getMaxUses() const;

    void resetAnim();
private:
    std::string name;
    int power;
    float healingPercentage;
    int nUsage;
    int maxUses;
    sf::Texture animationTexture;
    AnimatedSprite animation = AnimatedSprite(animationTexture, 427, 154, 8);
    Type type;
    int accuracy;
};


#endif //POKEMON_MOVE_H
