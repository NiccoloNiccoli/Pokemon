//
// Created by Niccolò Niccoli on 11/07/2020.
//

#ifndef POKEMON_DICE_H
#define POKEMON_DICE_H
#include "debug.h"

class Dice {
public:
    static int random(int min, int max);
    static int random(int max);
};


#endif //POKEMON_DICE_H
