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
    void setPosition(int x, int y);
    int winMoney(Trainer* opponent); //Print how much money you've won
    const std::string &getName() const;
    void draw(sf::RenderWindow& window, int row = 0);
    int getState() const;
    sf::Vector2f getPosition() const;
    sf::Rect<float> getGlobalBounds() const;
    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);
    void move(float x, float y);
    void setState(int state);
    int getMoney() const;
    void setMoney(int money);
    void healTeam();
    void drawInBattleSprite(sf::RenderWindow& window, int frequency, int row);
    void setInBattleSpritePosition(sf::Vector2f position);
    sf::Rect<float>getInBattleSpriteGlobalBounds();
    sf::Vector2f getInBattleSpritePosition();
    std::vector<Pokemon*> team;

protected:
    int id;
    std::string name;
    sf::Texture overworldSpriteTexture;
    AnimatedSprite overworldSprite = AnimatedSprite(overworldSpriteTexture,20,30,4);
    AnimatedSprite inBattleSprite;
    std::string spriteName;
    int money;
    int xPosition;
    int yPosition;
    int state=0;
    bool isStateUpdated = true;
};


#endif //POKEMON_TRAINER_H
