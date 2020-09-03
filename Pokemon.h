//
// Created by Niccolò Niccoli on 22/06/2020.
//

#ifndef POKEMON_POKEMON_H
#define POKEMON_POKEMON_H


#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Type.h"
#include "Move.h"
#include "AnimatedSprite.h"

class Pokemon {
public:
    Pokemon(const std::string& pokemonName,int lvl);
    int doMove(Move* move, Pokemon &enemy);
    void evolve();
    void setPosition(float x, float y);
    sf::Rect<float> getGlobalBounds();
    sf::Vector2f getPosition();
    void draw(sf::RenderWindow& window, int row);

    Move*getMoves(int index) const;
    int loseHp(int damage);

    bool isAlive() ;

    int getDefense() const;

    const std::string &getName() const;

    int getCurrentHp() const;

    int getMaxHp() const;

    int getAttack() const;

    int getSpeed() const;

    int getLevel() const;

    int gainEXP(Pokemon* enemy);

    int getExpToNextLevel() const;

    void setExpToNextLevel(int expToNextLevel);

    void heal();

private:
    int id;
    std::string name;
    sf::Texture texture;
    AnimatedSprite sprite = AnimatedSprite(texture,82,81,1);
    int currentHP = 0;
    int maxHP = 0;
    int attack;
    int defense;
    int speed;
    std::vector<Type> type;
    int level;
    int evolvingLevel;
    std::string nextFormName;
    bool alive = true;
    int expToNextLevel;
    Move* moves[4];

    void loadData(const std::string& pokemonName);
    void updateStats();
};


#endif //POKEMON_POKEMON_H
