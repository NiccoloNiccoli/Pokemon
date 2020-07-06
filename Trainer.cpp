//
// Created by Niccolò Niccoli on 19/06/2020.
//

#include "Trainer.h"
#include <SFML/Window.hpp>
#include <iostream>

Trainer::Trainer(int id, int x, int y){
    id = 0;
    xPosition = x;
    yPosition = y;
    initOverworldSprite("trainer.png");
    //FIXME-non so perché faccia così
    Pokemon pika("pikachu", 20);
    team.push_back(pika);
    team[0].sprite.setTexture(team[0].texture);
}

int Trainer::getId() const {
    return id;
}

void Trainer::setId(int id) {
    Trainer::id = id;
}

const std::string &Trainer::getName() const {
    return name;
}

void Trainer::setName(const std::string &name) {
    Trainer::name = name;
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

void Trainer::move(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        overworldSprite.move(1.,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        overworldSprite.move(-1.,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        overworldSprite.move(0,-1.);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        overworldSprite.move(0,1.);
    xPosition = getXPosition();
    yPosition = getYPosition();
}

bool Trainer::initOverworldSprite(std::string fileName){
    if(!overworldSprite_Texture.loadFromFile("../Textures/" + fileName)){
    //TODO handle error
    }
    sf::Vector2f position (xPosition,yPosition);
    overworldSprite.setPosition(position);
    overworldSprite.setTexture(overworldSprite_Texture);
    overworldSprite.setScale(0.5f,0.5f);

}

const sf::Sprite &Trainer::getOverworldSprite() const {
    return overworldSprite;
}

void Trainer::setOverworldSprite(const sf::Sprite &overworldSprite) {
    Trainer::overworldSprite = overworldSprite;
}

int Trainer::getXPosition() const {
    return xPosition;
}

void Trainer::setXPosition(int xPosition) {
    Trainer::xPosition = xPosition;
}

int Trainer::getYPosition() const {
    return yPosition;
}

void Trainer::setYPosition(int yPosition) {
    Trainer::yPosition = yPosition;
}

const int Trainer::getWidth() const {
    return width;
}

const int Trainer::getHeight() const {
    return height;
}
