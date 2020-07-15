//
// Created by Niccolò Niccoli on 19/06/2020.
//
#ifndef POKEMON_TRAINER_H
#define POKEMON_TRAINER_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Pokemon.h"
#include "debug.h"

class Trainer {
public:
    Trainer(int id, int x, int y, std::string trainerName, std::string spriteName);

    int getMoney() const;

    void setMoney(int money);

    int getXPosition() const;


    int getYPosition() const;


    int winMoney(Trainer& opponent, int prize); //Print how much money you've won

    const std::string &getName() const;

    sf::Sprite overworldSprite;
    std::vector<Pokemon*> team;

protected:
    bool initOverworldSprite(std::string fileName);

    int id;
    std::string name;

    sf::Texture overworldSprite_Texture;
    //TODO inBattleSprite
    int money;
    int xPosition;
    int yPosition;
};


#endif //POKEMON_TRAINER_H
