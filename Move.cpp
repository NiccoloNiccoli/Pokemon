//
// Created by Niccolò Niccoli on 23/06/2020.
//

#include <fstream>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Move.h"


Move::Move(const std::string& moveName) {
    try {
        std::ifstream file("../Pokemons/Moves/" + moveName + ".txt");
        if (file.is_open()) {
            std::string tmpType_string;
            name = moveName;
            file >> power >> healingPercentage >> nUsage >> tmpType_string >> accuracy;
            Type tmpType(tmpType_string);
            type = tmpType;
            maxUses = nUsage;
        }else{
            throw std::runtime_error("Unable to open: ../Pokemons/Moves/"+moveName+".txt");
        }
        file.close();
        if (!animationTexture.loadFromFile("../Pokemons/Moves/" + moveName + ".png")) {
            throw std::runtime_error("File not found: ../Pokemons/Moves/"+moveName+".png");
        }
        for (auto &c : name) {
            c = toupper(c);
        }
        std::replace(name.begin(), name.end(), '_', ' ');
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }

}

const std::string &Move::getName() const {
    return name;
}

int Move::getPower() const {
    return power;
}

float Move::getHealingPercentage() const {
    return healingPercentage;
}

int Move::getNUsage() const {
    return nUsage;
}

void Move::setNUsage(int _nUsage) {
    Move::nUsage = _nUsage;
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

Move::Move() : Move("quick_attack"){
}

int Move::getMaxUses() const {
    return maxUses;
}

void Move::resetAnim() {
    animation.resetFrame();
}
