//
// Created by Niccolò Niccoli on 10/07/2020.
//

#ifndef POKEMON_PLAYER_H
#define POKEMON_PLAYER_H


#include "Trainer.h"
#include "debug.h"
#include "NPC.h"

class Player : public Trainer {
public:
    Player(int id, int x, int y, std::string trainersName);

    void fight(NPC* enemy); //TODO fight-catch-escape

    bool catchPokemon(Pokemon* pokemon); //True if pokemon get caught, False if not

    int winMoney(NPC* opponent);

    bool escape(); //True if you run away, false if not

    void move();

    void setName(std::string playersName);
    bool isAnyPokemonAlive();
private:

};


#endif //POKEMON_PLAYER_H
