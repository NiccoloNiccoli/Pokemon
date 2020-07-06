//
// Created by Niccolò Niccoli on 23/06/2020.
//

#include <fstream>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Move.h"

Move::Move(const std::string& moveName){
    std::ifstream file("../Pokemons/Moves/" + moveName + ".txt");
    if (file.is_open()) {
        std::string tmpType_string;
        name = moveName;
        file >> power >> healingPercentage >> nUsage >> tmpType_string >> accuracy;
        Type tmpType(tmpType_string);
        type = tmpType;
       std::cout << name << " Power: " << power << " Healing percentage: " << healingPercentage << " Number of usage: " << nUsage <<
        " Type: " << type.getTypeName() << " Accuracy: " << accuracy << std::endl;
    }
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

void Move::playAnimation(sf::RenderWindow& window){
    sf::Clock timer;
    for(int i = 0; i < power/30; i++){
        timer.restart();
        while(timer.getElapsedTime().asSeconds() < 0.1f){
            window.clear(sf::Color::White);
            window.display();
        }
        while(timer.getElapsedTime().asSeconds() < 0.2f){
           if(type.getTypeName() == "normal"){
               window.clear(sf::Color::Black);
           }else if(type.getTypeName() == "fire"){
               window.clear(sf::Color::Red);
           }else if(type.getTypeName() == "electric"){
               window.clear(sf::Color::Yellow);
           }else if(type.getTypeName() == "water"){
               window.clear(sf::Color::Cyan);
           }

            window.display();
        }
    }

}