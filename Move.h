//
// Created by super on 23/06/2020.
//

#ifndef POKEMON_MOVE_H
#define POKEMON_MOVE_H


#include <string>
#include "Type.h"

class Move {
public:
    Move(const std::string& moveName);
    void use();

private:

    int hit();
    int heal();

    std::string name;
public:
    const std::string &getName() const;

private:
    int power;
    float healingPercentage;
    int n_usage;
    //TODO animation(?)
    Type type;
    float accuracy;
};


#endif //POKEMON_MOVE_H
