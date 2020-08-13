//
// Created by Niccolò Niccoli on 19/06/2020.
//
#ifndef POKEMON_TRAINER_H
#define POKEMON_TRAINER_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Pokemon.h"
#include "debug.h"
#include "AnimatedSprite.h"

class Trainer {
public:
    Trainer(int ID, int x, int y);

    int getXPosition() const;


    int getYPosition() const;
    void setPosition(int x, int y);

   int winMoney(Trainer* opponent); //Print how much money you've won

    const std::string &getName() const;

    void draw(sf::RenderWindow& window, int row = 0);
    int getState() const;
    AnimatedSprite overworldSprite = AnimatedSprite(overworldSpriteTexture,20,30,4);
    std::vector<Pokemon*> team;

    void setState(int state);

    int getMoney() const;
    void setMoney(int money);

    void setIsStateUpdated(bool isStateUpdated);

protected:
    int id;
    std::string name;
    sf::Texture overworldSpriteTexture;
    //TODO inBattleSprite
    int money;
    int xPosition;
    int yPosition;
    int state=0;
    bool isStateUpdated = true;
};


#endif //POKEMON_TRAINER_H
