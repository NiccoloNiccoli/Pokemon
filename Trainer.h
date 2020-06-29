//
// Created by Niccolò Niccoli on 19/06/2020.
//

#ifndef POKEMON_TRAINER_H
#define POKEMON_TRAINER_H
#include <string>
#include <SFML/Graphics.hpp>

class Trainer {
public:
    Trainer(int id, int x, int y);

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getMoney() const;

    void setMoney(int money);

    const sf::Sprite &getOverworldSprite() const;

    void setOverworldSprite(const sf::Sprite &overworldSprite);

    int getXPosition() const;

    void setXPosition(int xPosition);

    int getYPosition() const;

    void setYPosition(int yPosition);

    const int getWidth() const;

    const int getHeight() const;

    void move();

    void fight(); //TODO fight-catch-escape

    bool catchPokemon(); //True if pokemon get caught, False if not

    bool escape(); //True if you run away, false if not

    int winMoney(Trainer& opponent, int prize); //Print how much money you've won



    sf::Sprite overworldSprite;



private:
    bool initOverworldSprite(std::string fileName);

    int id;
    std::string name;
    //TODO Pokemon[n] team;
    sf::Texture overworldSprite_Texture;
    //TODO inBattleSprite
    int money;
    int xPosition;
    int yPosition;
    const int width = 32;
    const int height = 32;

};


#endif //POKEMON_TRAINER_H
