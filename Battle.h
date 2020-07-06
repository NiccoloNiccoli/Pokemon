//
// Created by Niccolò Niccoli on 25/06/2020.
//

#ifndef POKEMON_BATTLE_H
#define POKEMON_BATTLE_H
#include <SFML/Graphics.hpp>
#include "Trainer.h"
#include "Pokemon.h"

//FIXME farlo meglio!!!!!
extern bool isInBattle;
extern Pokemon* wildPokemon;
extern sf::Clock timer;

class Battle {
public:
    Battle(Trainer& player, Pokemon& pokemon);
    void draw(sf::RenderWindow& window, Trainer& player, Pokemon& pokemon);
    void moveUp();
    void moveDown();
    void refreshMenu(Trainer& player, Pokemon& enemy, sf::RenderWindow& window);//Fixme find a better way to do it
    void resetMenu();
    void battleEngine(sf::RenderWindow& window, Trainer& player, Pokemon& enemy);//FIXME change its name

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
    void updateUI(Trainer& player, Pokemon& pokemon);

    int menuPageIndex;
    //page 0 -> actions page 1 -> moves page 2 -> show team to change active pokemon
    int selectedItemIndex;
    sf::Font font;
    sf::Texture background_texture;



};


#endif //POKEMON_BATTLE_H
