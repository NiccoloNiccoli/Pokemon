//
// Created by Niccolò Niccoli on 08/07/2020.
//

#include "Tile.h"
Tile::Tile(const int currentTileValue){
    value = currentTileValue;
    switch(value){
        case 1:
            type = TALL_GRASS;
            break;

        case 117:
            type = POKEMON_CENTER_DOOR;
            break;

            //Pokemon center walls tiles
        case 68:
        case 69:
        case 70:
        case 71:
        case 84:
        case 85:
        case 86:
        case 87:
        case 100:
        case 101:
        case 102:
        case 103:
        case 116:
        case 118:
        case 119:
            //Trees tiles
        case 88:
        case 89:
        case 134:
        case 135:
        case 150:
        case 151:
        case 164:
        case 166:
        case 167:
        case 168:
        case 182:
        case 184:
        case 198:
        case 199:
            type = NOT_WALKABLE;
        break;
        default:
            type = WALKABLE;
    }
}

int Tile::getValue() const {
    return value;
}

TypeOfTile Tile::getType() const {
    return type;
}
