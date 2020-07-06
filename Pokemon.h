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
    bool doMove(Move& move, Pokemon& enemy, sf::RenderWindow& window);
    void evolve(); //TODO->copia di tutti i valori in un nuovo pokemon
    sf::Sprite sprite;
    sf::Texture texture;
    void draw(sf::RenderWindow& window);
    std::vector<Move> moves;
    void loseHp(const int damage);

    bool isAlive() ;

    int getDefense() const;

    const std::string &getName() const;

    int getCurrentHp() const;

    int getMaxHp() const;

    int getSpeed() const;

    int getLevel() const;



private:
    int id;
    std::string name;


    int currentHP;
    int maxHP;
    int attack;
    int defense;
    int speed;
    std::vector<Type> type;

    //TODO Ability
    bool isWild;
    int level;
    int evolvingLevel;
    int nextFormId;
    bool alive = true;

    bool loadData(const std::string& pokemonName);
};


#endif //POKEMON_POKEMON_H
