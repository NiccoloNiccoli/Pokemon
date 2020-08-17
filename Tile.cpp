//
// Created by Niccolò Niccoli on 08/07/2020.
//

#include <string>
#include "Tile.h"
Tile::Tile(const int currentTileValue,const std::string& tileset){
    value = currentTileValue;
    if(tileset == "tileset1_1.png"){
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
    }else if(tileset == "tileset2.png"){
        switch (value){
           case 54:
               case 55:
                type = POKEMON_CENTER_DOOR;
                break;

            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 58:
            case 64:
                type = NOT_WALKABLE;
                break;
            default:
                type = WALKABLE;
        }
    }

}

int Tile::getValue() const {
    return value;
}

TypeOfTile Tile::getType() const {
    return type;
}
