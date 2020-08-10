//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "State.h"

State::State(Game* gamePtr) {
    game = gamePtr;
}

GameState State::getStateName() {
    return stateName;
}
