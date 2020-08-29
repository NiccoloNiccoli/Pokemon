//
// Created by Niccolò Niccoli on 19/06/2020.
//

#include "Trainer.h"
#include "Battle.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

Trainer::Trainer(int ID, int x, int y) {
    try {
        id = ID;
        std::ifstream trainerData("../Trainers/" + std::to_string(id) + ".txt");
        if (trainerData.is_open()) {
            trainerData >> name >> spriteName;
            int max;
            trainerData >> max;

            for (int i = 0; i < max; i++) {
                std::string pokemonName;
                int level;
                trainerData >> pokemonName >> level;
                team.emplace_back(new Pokemon(pokemonName, level));
            }
            trainerData >> money;
        } else {
            throw std::runtime_error("Unable to open: ../Trainers/" + std::to_string(id) + ".txt");
        }

        xPosition = x;
        yPosition = y;
        if (!overworldSpriteTexture.loadFromFile("../Textures/" + spriteName)) {
            throw std::runtime_error("File not found: ../Textures/" + spriteName);
        }
        sf::Vector2f position(xPosition, yPosition);
        overworldSprite.setPosition(position);
    }catch(const std::runtime_error& ex){
        std::cerr<<ex.what()<<std::endl;
        exit(-1);
    }
}

int Trainer::winMoney(Trainer* opponent){
    int prize = 0;
    if(opponent->money > 0){
        //You win always 10% of opponent's max money
        prize = static_cast<int>(opponent->money * 0.1);
        opponent->money -= prize;
        money += prize;
#ifdef DEBUG
        std::cout<<name<<" ha vinto "<<prize<<std::endl;
#endif
    }
    return prize;
}

const std::string &Trainer::getName() const {
    return name;
}

void Trainer::draw(sf::RenderWindow &window, int row) {
    overworldSprite.draw(window,8,row);
}

int Trainer::getState() const {
    return state;
}

int Trainer::getMoney() const {
    return money;
}

void Trainer::setMoney(int _money) {
    Trainer::money = _money;
}

void Trainer::setPosition(int x, int y) {
    overworldSprite.setPosition(x,y);
}

void Trainer::setState(int _state) {
    Trainer::state = _state;
}

void Trainer::healTeam() {
    for(int i = 0;i < team.size(); i++)
        team[i]->heal();
#ifdef DEBUG
    std::cout<<"team healed!"<<std::endl;
#endif
}

sf::Vector2f Trainer::getPosition() const {
    return overworldSprite.getPosition();
}

sf::Rect<float> Trainer::getGlobalBounds() const {
    return overworldSprite.getGlobalBounds();
}

void Trainer::setPosition(const sf::Vector2f& position) {
    overworldSprite.setPosition(position);
}
void Trainer::setPosition(float x, float y) {
    overworldSprite.setPosition(x,y);
}


void Trainer::move(float x, float y) {
    overworldSprite.move(x,y);
}

void Trainer::drawInBattleSprite(sf::RenderWindow &window, int frequency, int row) {
    inBattleSprite.draw(window,frequency,row);
}

void Trainer::setInBattleSpritePosition(sf::Vector2f position) {
    inBattleSprite.setPosition(position);
}

sf::Rect<float> Trainer::getInBattleSpriteGlobalBounds() {
    return inBattleSprite.getGlobalBounds();
}

sf::Vector2f Trainer::getInBattleSpritePosition() {
    return inBattleSprite.getPosition();
}

