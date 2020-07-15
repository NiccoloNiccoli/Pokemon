//
// Created by Niccolò Niccoli on 19/06/2020.
//

#include "Trainer.h"
#include <SFML/Window.hpp>
#include <iostream>

Trainer::Trainer(int id, int x, int y, std::string trainerName, std::string spriteName){
    id = 0;
    xPosition = x;
    yPosition = y;
    name = trainerName;
    initOverworldSprite(spriteName);
    //FIXME-non so perché faccia così
    Pokemon* pika;
    pika = new Pokemon("pikachu", 20);
    team.push_back(pika);
#ifdef DEBUG
    std::cout<<team[0]->getName()<<" is a beautiful pokemon(?)"<<std::endl;
#endif
}

int Trainer::getMoney() const {
    return money;
}

void Trainer::setMoney(int money) {
    Trainer::money = money;
}
int Trainer::winMoney(Trainer& opponent, int prize){
    if(opponent.getMoney() > 0){
        //You win always 10% of opponent's max money
        prize = opponent.getMoney() * 0.1;
        opponent.setMoney(opponent.getMoney()-prize);
        Trainer::setMoney(prize);
    }
}

bool Trainer::initOverworldSprite(std::string fileName){
    if(!overworldSprite_Texture.loadFromFile("../Textures/" + fileName)){
    //TODO handle error
    }
    sf::Vector2f position (xPosition,yPosition);
    overworldSprite.setPosition(position);
    overworldSprite.setTexture(overworldSprite_Texture);
}

int Trainer::getXPosition() const {
    return overworldSprite.getPosition().x;
}

int Trainer::getYPosition() const {
    return overworldSprite.getPosition().y;
}

const std::string &Trainer::getName() const {
    return name;
}
