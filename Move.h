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
    Move(const std::string& moveName);
    void draw(sf::RenderWindow& window);
    void use();

    int getPower() const;

    void setPower(int power);

    float getHealingPercentage() const;

    void setHealingPercentage(float healingPercentage);

    int getNUsage() const;

    void setNUsage(int nUsage);

    const std::string &getName() const;

    const Type &getType() const;

    int getAccuracy() const;

    int getMaxUses() const;

private:
    std::string name;
    int power;
    float healingPercentage;
    int nUsage;
    int maxUses;
    //TODO sf::Texture animationTexture;
    //TODO AnimatedSprite animation = AnimatedSprite(animationTexture,1,1,1);
    Type type;
    int accuracy;
};


#endif //POKEMON_MOVE_H
