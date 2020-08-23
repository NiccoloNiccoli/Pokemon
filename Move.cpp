//
// Created by Niccolò Niccoli on 23/06/2020.
//

#include <fstream>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Move.h"
#include "Game.h"

Move::Move(const std::string& moveName){
    std::ifstream file("../Pokemons/Moves/" + moveName + ".txt");
    if (file.is_open()) {
        std::string tmpType_string;
        name = moveName;
        file >> power >> healingPercentage >> nUsage >> tmpType_string >> accuracy;
        Type tmpType(tmpType_string);
        type = tmpType;
#ifdef DEBUG
       std::cout << name << " Power: " << power << " Healing percentage: " << healingPercentage << " Number of usage: " << nUsage <<
        " Type: " << type.getTypeName() << " Accuracy: " << accuracy << std::endl;
#endif
       maxUses = nUsage;
    }
        if (!animationTexture.loadFromFile("../Pokemons/Moves/" + moveName + ".png")) {
            //TODO error
        }
        animation = AnimatedSprite(animationTexture, 427, 154, 8);
    for (auto &c : name){
        c = toupper(c);
    }
    std::replace(name.begin(),name.end(),'_', ' ');
}

const std::string &Move::getName() const {
    return name;
}

int Move::getPower() const {
    return power;
}

void Move::setPower(int power) {
    Move::power = power;
}

float Move::getHealingPercentage() const {
    return healingPercentage;
}

void Move::setHealingPercentage(float healingPercentage) {
    Move::healingPercentage = healingPercentage;
}

int Move::getNUsage() const {
    return nUsage;
}

void Move::setNUsage(int nUsage) {
    Move::nUsage = nUsage;
}

int Move::getAccuracy() const {
    return accuracy;
}

const Type &Move::getType() const {
    return type;
}

void Move::draw(sf::RenderWindow& window, int row) {
    animation.draw(window,8,row);
}

Move::Move() {
    Move("quick_attack");
}

int Move::getMaxUses() const {
    return maxUses;
}
