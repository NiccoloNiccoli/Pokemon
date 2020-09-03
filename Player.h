//
// Created by Niccolò Niccoli on 10/07/2020.
//

#ifndef POKEMON_PLAYER_H
#define POKEMON_PLAYER_H


#include "Trainer.h"
#include "NPC.h"

class Player : public Trainer {
public:
    Player(int id, int x, int y, const std::string& trainersName);

    void fight(NPC* enemy);

    bool catchPokemon(Pokemon* pokemon); //True if pokemon get caught, False if not

    int winMoney(NPC* opponent);

    void move();

    void setName(const std::string& playersName);
    bool isAnyPokemonAlive();
private:
    sf::Texture inBattleSpriteTexture;

};


#endif //POKEMON_PLAYER_H
