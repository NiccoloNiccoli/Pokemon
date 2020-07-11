//
// Created by Niccolò Niccoli on 25/06/2020.
//

#ifndef POKEMON_BATTLE_H
#define POKEMON_BATTLE_H
#include <SFML/Graphics.hpp>
#include "Trainer.h"
#include "Pokemon.h"
#include "debug.h"
#include "Player.h"

//FIXME farlo meglio!!!!!

class Battle {
public:
    Battle(Player& player);
    void draw(sf::RenderWindow& window, Player& player);
    void moveUp();
    void moveDown();
    void refreshMenu(Player& player, sf::RenderWindow& window);//Fixme find a better way to do it
    void resetMenu();
    void battleEngine(sf::RenderWindow& window, Player& player);//FIXME change its name

    static void setWildPokemon(Pokemon* pokemon);

    sf::Sprite background;
    sf::RectangleShape menuBox;
    sf::Text menuButtons[4];
    sf::RectangleShape myHealthBarBox;
    sf::RectangleShape enemysHealthBarBox;
    sf::RectangleShape myHealthBar;
    sf::RectangleShape enemysHealthBar;
    sf::Text myPokemonName;
    sf::Text enemysPokemonName;
    sf::Text myPokemonLevel;
    sf::Text enemysPokemonLevel;

    //FIXME
    int haveYouSelectedAnAction = 0;
private:
    void updateUI(Player& player);
    static Pokemon* wildPokemon;
    int menuPageIndex = 1;
    //page 0 -> actions page 1 -> moves page 2 -> show team to change active pokemon
    int selectedItemIndex = 0;
    sf::Font font;
    sf::Texture background_texture;



};

#endif //POKEMON_BATTLE_H
