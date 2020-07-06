//
// Created by Niccolò Niccoli on 23/06/2020.
//

#ifndef POKEMON_MOVE_H
#define POKEMON_MOVE_H


#include <string>
#include "Type.h"

class Move {
public:
    Move(const std::string& moveName);
    void playAnimation(sf::RenderWindow& window);
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

private:
    std::string name;
    int power;
    float healingPercentage;
    int nUsage;
    //TODO animation(?)
    Type type;
    int accuracy;

    int hit();
    int heal();
};


#endif //POKEMON_MOVE_H
