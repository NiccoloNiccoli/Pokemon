//
// Created by Niccolò Niccoli on 19/06/2020.
//

#include "Trainer.h"
#include "Battle.h"
#include <SFML/Window.hpp>
#include <iostream>

Trainer::Trainer(int ID, int x, int y){
    id = ID;
    std::string spriteName;
    std::string trainerName;
    switch(id){
        case 0:
            //player
            spriteName = "player.png";
            Pokemon* pika;
            pika = new Pokemon ("Pikachu",20);
            team.emplace_back(pika);
            money = 1000;
            break;
        case 1:
            //rival
            trainerName = "Blue";
            spriteName = "blue.png";
            Pokemon* squirtle1;
            squirtle1 = new Pokemon ("Squirtle",20);
            team.emplace_back(squirtle1);
            money = 1000;
            break;
        case 2:
            //lance
            trainerName = "Lance";
            spriteName = "lance.png";
            Pokemon* charmander2;
            charmander2 = new Pokemon ("charmander",20);
            team.emplace_back(charmander2);
            money = 1000;
            break;
        case 3:
            //girl
            trainerName = "Megan";
            spriteName = "girl.png";
            Pokemon* pikachu3;
            pikachu3 = new Pokemon ("Pikachu",15);
            team.emplace_back(pikachu3);
            money = 1000;
            break;
    }
    xPosition = x;
    yPosition = y;
    name = trainerName;
    initOverworldSprite(spriteName);
}

int Trainer::winMoney(Trainer* opponent){
    //TODO impedire che si possa chiedere i soldi più volte di fila alla stessa persona solo perché ha il pokemon morto
    if(opponent->money > 0){
        int prize;
        //You win always 10% of opponent's max money
        prize = opponent->money * 0.1;
        opponent->money -= prize;
        Trainer::money += prize;
        Battle::changeBattleLog(name+" has won "+opponent->name+"$!");
#ifdef DEBUG
        std::cout<<name<<" ha vinto "<<prize<<std::endl;
#endif
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
