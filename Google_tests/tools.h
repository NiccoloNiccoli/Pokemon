//
// Created by Niccolò Niccoli on 14/08/2020.
//

#ifndef POKEMON_TOOLS_H
#define POKEMON_TOOLS_H

#include <cmath>

void statCalc(int level, int level1, int &attack, int &defense);

void doDamage(int levelAttacker, int levelDefender, int attack, int defense, int power, float typeAdvantage, float STAB, int& damageMax, int& damageMin){
    float modifier;
    statCalc(levelAttacker, levelDefender, attack, defense);
    modifier = 0.85 *typeAdvantage*STAB;
    damageMin=powf((((2/5 * levelAttacker + 2) * power * attack/defense)/50 + 2),1.5) * modifier;
    modifier = 1.5 * typeAdvantage*STAB;
    damageMax =powf((((2/5 * levelAttacker + 2) * power * attack/defense)/50 + 2),1.5) * modifier;
}

void statCalc(int levelAttacker, int levelDefender, int &baseAttack, int &baseDefense) {
    baseAttack = ((2*baseAttack+48)*levelAttacker)/100 + 5;
    baseDefense = ((2*baseDefense+48)*levelDefender)/100 + 5;
}

#endif //POKEMON_TOOLS_H
