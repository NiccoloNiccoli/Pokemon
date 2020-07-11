//
// Created by Niccolò Niccoli on 25/06/2020.
//

#include <iostream>
#include <string>
#include "Battle.h"
#include "GameState.h"
#include "Player.h"

Pokemon Battle::wildPokemon ("Pikachu",1);

Battle::Battle(Player& player){
    if(!background_texture.loadFromFile("../Textures/background.png")){
        //TODO handle error
    }
    background.setTexture(background_texture);
    background.setScale(0.35f,0.35f);
    sf::RectangleShape tmpBox (sf::Vector2f(120.f,100.f));
    tmpBox.setFillColor(sf::Color::White);
    tmpBox.setPosition(sf::Vector2f(300, 135));
    menuBox = tmpBox;
    if(!font.loadFromFile("../pokemon_pixel_font.ttf")){
        //TODO handle error
    }
    //initializing buttons "FIGHT", "SWAP", "CATCH", "RUN"
    resetMenu();

    //HP bar
    sf::RectangleShape tmpHpBox (sf::Vector2f(100, 40));
    tmpHpBox.setFillColor(sf::Color::White);
    myHealthBarBox = tmpHpBox;
    myHealthBarBox.setPosition(sf::Vector2f(0, 100));
    enemysHealthBarBox = tmpHpBox;
    enemysHealthBarBox.setPosition(sf::Vector2f(130,5));
    sf::RectangleShape tmpHpBar (sf::Vector2f(80, 10));
    tmpHpBar.setFillColor(sf::Color::Green);
    myHealthBar = tmpHpBar;
    myHealthBar.setPosition(sf::Vector2f(5,120));
    enemysHealthBar = tmpHpBar;
    enemysHealthBar.setPosition(sf::Vector2f(135,25));
    myPokemonName.setFont(font);
    myPokemonName.setFillColor(sf::Color::Black);
    myPokemonName.setPosition(sf::Vector2f(5, 100));
    myPokemonName.setScale(sf::Vector2f(0.5f,0.5f));
    enemysPokemonName.setFont(font);
    enemysPokemonName.setFillColor(sf::Color::Black);
    enemysPokemonName.setPosition(sf::Vector2f(135, 5));
    enemysPokemonName.setScale(sf::Vector2f(0.5f,0.5f));
    myPokemonLevel.setFont(font);
    myPokemonLevel.setFillColor(sf::Color::Black);
    myPokemonLevel.setPosition(sf::Vector2f(70, 105));
    myPokemonLevel.setScale(sf::Vector2f(0.3f, 0.3f));
    enemysPokemonLevel.setFont(font);
    enemysPokemonLevel.setFillColor(sf::Color::Black);
    enemysPokemonLevel.setPosition(sf::Vector2f(200, 10));
    enemysPokemonLevel.setScale(sf::Vector2f(0.3f, 0.3f));
#ifdef DEBUG
    std::cout<<"Battle created"<<std::endl;
    resetMenu();
#endif
}

void Battle::draw(sf::RenderWindow &window, Player& player) {
    window.draw(background);
    window.draw(menuBox);
    for(auto i : menuButtons)
        window.draw(i);
    player.team[0].sprite.setPosition(40,100);
    window.draw(player.team[0].sprite);
    wildPokemon.sprite.setPosition(240,0);
    wildPokemon.draw(window);
    updateUI(player);
    window.draw(myHealthBarBox);
    window.draw(enemysHealthBarBox);
    window.draw(myHealthBar);
    window.draw(enemysHealthBar);
    window.draw(myPokemonName);
    window.draw(enemysPokemonName);
    myPokemonName.setString(player.team[0].getName());
    enemysPokemonName.setString(wildPokemon.getName());
    myPokemonLevel.setString("L." + std::to_string(player.team[0].getLevel()));
    enemysPokemonLevel.setString("L. " + std::to_string(wildPokemon.getLevel()));
    window.draw(myPokemonLevel);
    window.draw(enemysPokemonLevel);
}


void Battle::moveUp(){
    menuButtons[abs(selectedItemIndex)%4].setFillColor(sf::Color::Black);
    selectedItemIndex--;
    if(selectedItemIndex == -1)
        selectedItemIndex = 3;
    menuButtons[abs(selectedItemIndex)%4].setFillColor(sf::Color::Red);

}

void Battle::moveDown() {
    menuButtons[selectedItemIndex%4].setFillColor(sf::Color::Black);
    selectedItemIndex++;
    if(selectedItemIndex == 4)
        selectedItemIndex = 0;
    menuButtons[selectedItemIndex%4].setFillColor(sf::Color::Red);

}

void Battle::refreshMenu(Player& player, sf::RenderWindow& window) {
    if(menuPageIndex == 0){
        switch (selectedItemIndex){
            case 0:
                menuButtons[0].setString(player.team[0].moves[0].getName());
                menuButtons[0].setScale(sf::Vector2f(0.4f,0.4f));
                menuButtons[1].setString(player.team[0].moves[1].getName());
                menuButtons[1].setScale(sf::Vector2f(0.4f,0.4f));
                menuButtons[2].setString(player.team[0].moves[2].getName());
                menuButtons[2].setScale(sf::Vector2f(0.4f,0.4f));
                menuButtons[3].setString(player.team[0].moves[3].getName());
                menuButtons[3].setScale(sf::Vector2f(0.4f,0.4f));
                menuPageIndex = 1;
                break;
            case 1:
                //TODO swap pokemon
                break;
            case 2:
                player.catchPokemon(wildPokemon);
            case 3:
                GameState::changeState(STATE_MAP);
                GameState::resetTimer();
#ifdef DEBUG
                for(auto i:player.team)
                    std::cout<<i.getName()<<std::endl;
#endif
                break;
        }
    }else if(menuPageIndex == 1){
        if(player.team[0].moves[selectedItemIndex].getNUsage() > 0){
            haveYouSelectedAnAction = selectedItemIndex+1;
            resetMenu();
        }else{
#ifdef DEBUG
            std::cerr<<"You can't use this move"<<std::endl;
#endif
        }

    }
}

void Battle::resetMenu() {
    if(menuPageIndex!=0){
        menuButtons[0].setFont(font);
        menuButtons[0].setFillColor(sf::Color::Red);
        menuButtons[0].setString("FIGHT");
        menuButtons[0].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 10));
        menuButtons[0].setScale(0.8f, 0.8f);

        menuButtons[1].setFont(font);
        menuButtons[1].setFillColor(sf::Color::Black);
        menuButtons[1].setString("SWAP");
        menuButtons[1].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 50));
        menuButtons[1].setScale(0.8f, 0.8f);

        menuButtons[2].setFont(font);
        menuButtons[2].setFillColor(sf::Color::Black);
        menuButtons[2].setString("CATCH");
        menuButtons[2].setPosition(sf::Vector2f(menuBox.getPosition().x + 65, menuBox.getPosition().y + 10));
        menuButtons[2].setScale(0.8f, 0.8f);

        menuButtons[3].setFont(font);
        menuButtons[3].setFillColor(sf::Color::Black);
        menuButtons[3].setString("RUN");
        menuButtons[3].setPosition(sf::Vector2f(menuBox.getPosition().x + 65, menuBox.getPosition().y + 50));
        menuButtons[3].setScale(0.8f, 0.8f);

        selectedItemIndex = 0;
        menuPageIndex=0;
#ifdef DEBUG
        std::cout<<"menu resetted"<<std::endl;
#endif
    }

}

void Battle::updateUI(Player& player) {
    myHealthBar.setSize(sf::Vector2f(80*player.team[0].getCurrentHp()/player.team[0].getMaxHp(),10.f));
    enemysHealthBar.setSize(sf::Vector2f(80 * wildPokemon.getCurrentHp()/wildPokemon.getMaxHp(),10.f));
}

void Battle::battleEngine(sf::RenderWindow &window, Player &player) {
    if(player.team[0].isAlive() && wildPokemon.isAlive()){
//battle cycle
        draw(window, player);
        if(haveYouSelectedAnAction == 0){


        }else{
            //wildPokemon does a random move
            if(player.team[0].getSpeed() > wildPokemon.getSpeed()){
                //i go first
                player.team[0].doMove(player.team[0].moves[haveYouSelectedAnAction-1], wildPokemon, window);
                if(wildPokemon.isAlive() && player.team[0].isAlive()){
                    //wildPokemon does a random move
                    int r = rand()%4;
                    wildPokemon.doMove(wildPokemon.moves[r], player.team[0], window);
                }
            }else if(player.team[0].getSpeed() < wildPokemon.getSpeed()){
                //wildPokemon goes first
                int r = rand()%4;
                wildPokemon.doMove(wildPokemon.moves[r], player.team[0], window);
                if(wildPokemon.isAlive() && player.team[0].isAlive())
                    player.team[0].doMove(player.team[0].moves[haveYouSelectedAnAction-1], wildPokemon, window);
            }else{
                int r = rand()%2;
                if (r==0){
                    //i go first
                    player.team[0].doMove(player.team[0].moves[haveYouSelectedAnAction-1], wildPokemon, window);
                    if(wildPokemon.isAlive() && player.team[0].isAlive()){
                        //wildPokemon does a random move
                        int r = rand()%4;
                        wildPokemon.doMove(wildPokemon.moves[r], player.team[0], window);
                    }
                }else{
                    int r = rand()%4;
                    wildPokemon.doMove(wildPokemon.moves[r], player.team[0], window);
                    if(wildPokemon.isAlive() && player.team[0].isAlive())
                        player.team[0].doMove(player.team[0].moves[haveYouSelectedAnAction-1], wildPokemon, window);
                }
            }
            haveYouSelectedAnAction = 0;
        }

    }else{
        GameState::changeState(STATE_MAP);
        GameState::resetTimer();
    }
}

void Battle::setWildPokemon(Pokemon& pokemon) {
    wildPokemon = pokemon;
    wildPokemon.sprite.setTexture(wildPokemon.texture);
}