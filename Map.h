//
// Created by Niccolò Niccoli on 08/07/2020.
//

#ifndef POKEMON_MAP_H
#define POKEMON_MAP_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Trainer.h"
#include "Player.h"
#include "debug.h"
#include "NPC.h"

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map(const std::string& tilesetName, unsigned int mapColumns, unsigned int mapRows,
        const std::string& mapName, sf::Vector2u tileSize_ = sf::Vector2u(16,16));
    void checkCollisions(Trainer& player);
    void drawUI(sf::RenderWindow& window);
    void drawNPC(sf::RenderWindow& window);
    NPC* lookForNearestEnemy(const Player& player);
    const std::string &getName() const;
    void restartTimer();
    sf::Vector2f findPokemonCenterDoor();


private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void loadMap(const std::string& mapName,const std::string& tilesetName);
    unsigned int columns;
    unsigned int rows;
    sf::Vector2f oldPlayerPosition = sf::Vector2f(0,0);
    sf::Vector2u tileSize;
    sf::VertexArray vertices;
    sf::Texture tileset;
    std::vector<Tile> tiles;
    sf::Text name;
    std::string _name;

    sf::Sprite box;
    sf::Texture boxTexture;
    sf::Font font;
    std::vector<NPC*> npc;
    sf::Clock timer;


    unsigned int averagePokemonLevel;
    std::vector<std::string> wildPokemons;

};


#endif //POKEMON_MAP_H
