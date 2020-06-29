//
// Created by Niccolò Niccoli on 22/06/2020.
//

#ifndef POKEMON_POKEMON_H
#define POKEMON_POKEMON_H


#include <string>
#include <SFML/Graphics.hpp>
#include "Type.h"
#include "Move.h"

class Pokemon {
public:
    Pokemon(const std::string& pokemonName, unsigned int);
    bool doMove(); //TODO
    void evolve(); //TODO->copia di tutti i valori in un nuovo pokemon
    bool checkStatus(); //TODO: is dead or not?
    sf::Sprite sprite;
private:
    int id;
    std::string name;

    sf::Texture texture;
    int currentHP;
    int maxHP;
    int attack;
    int defense;
    int speed;
    std::vector<Type> type;
    std::vector<Move> moves;
    //TODO Ability, Moves
    bool isWild;
    int level;
    int evolvingLevel;
    int nextFormId;

    bool loadData(const std::string& pokemonName);
};


#endif //POKEMON_POKEMON_H
