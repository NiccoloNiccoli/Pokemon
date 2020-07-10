//
// Created by Niccolò Niccoli on 10/07/2020.
//

#ifndef POKEMON_PLAYER_H
#define POKEMON_PLAYER_H


#include "Trainer.h"
#include "debug.h"

class Player : public Trainer {
public:
    Player(int id, int x, int y, std::string trainerName, std::string spriteName = "player.png");

    void fight(Trainer& trainer); //TODO fight-catch-escape

    bool catchPokemon(); //True if pokemon get caught, False if not

    bool escape(); //True if you run away, false if not

    void move();
private:

};


#endif //POKEMON_PLAYER_H
