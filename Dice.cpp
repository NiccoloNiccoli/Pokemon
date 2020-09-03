//
// Created by Niccolò Niccoli on 11/07/2020.
//

#include <iostream>
#include "Dice.h"
int Dice::random(int min, int max){
    int diff = max - min;
    return rand()%diff + min;
}
int Dice::random(int max){
    return rand()%max;
}