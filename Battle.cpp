//
// Created by Niccolò Niccoli on 25/06/2020.
//

#include <iostream>
#include <string>
#include "Battle.h"
#include "Player.h"
#include "Dice.h"
#include "Game.h"

Pokemon* Battle::wildPokemon = nullptr;
Trainer* Battle::trainer = nullptr;
sf::Text Battle::battleLog;

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
    if(!font.loadFromFile("../pkmnem.ttf")){
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
    myPokemonName.setPosition(sf::Vector2f(5, 105));
    myPokemonName.setScale(sf::Vector2f(0.35f,0.35f));
    enemysPokemonName.setFont(font);
    enemysPokemonName.setFillColor(sf::Color::Black);
    enemysPokemonName.setPosition(sf::Vector2f(135, 10));
    enemysPokemonName.setScale(sf::Vector2f(0.35f,0.35f));
    myPokemonLevel.setFont(font);
    myPokemonLevel.setFillColor(sf::Color::Black);
    myPokemonLevel.setPosition(sf::Vector2f(70, 105));
    myPokemonLevel.setScale(sf::Vector2f(0.2f, 0.2f));
    enemysPokemonLevel.setFont(font);
    enemysPokemonLevel.setFillColor(sf::Color::Black);
    enemysPokemonLevel.setPosition(sf::Vector2f(200, 10));
    enemysPokemonLevel.setScale(sf::Vector2f(0.2f, 0.2f));
    sf::RectangleShape tmpDialogBox (sf::Vector2f(250.f,40.f));
    tmpDialogBox.setFillColor(sf::Color::White);
    tmpDialogBox.setPosition(28.f,190.f);
    dialogBox = tmpDialogBox;
    battleLog.setFont(font);
    battleLog.setFillColor(sf::Color::Black);
    battleLog.setPosition(35.f,195.f);
    battleLog.setScale(0.6f,0.6f);
    battleLog.setString("What will "+player.team[0]->getName()+" do?");
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
    player.team[0]->sprite.setPosition(40,100);
    window.draw(player.team[0]->sprite);
    myPokemonName.setString(player.team[0]->getName());
    myPokemonLevel.setString("L." + std::to_string(player.team[0]->getLevel()));
    if(trainer == nullptr && wildPokemon != nullptr){
        wildPokemon->sprite.setPosition(240,0);
        wildPokemon->draw(window);
        enemysPokemonName.setString(wildPokemon->getName());
        enemysPokemonLevel.setString("L. " + std::to_string(wildPokemon->getLevel()));
    }else{
        trainer->team[0]->sprite.setPosition(240,0);
        trainer->team[0]->draw(window);
        enemysPokemonName.setString(trainer->team[0]->getName());
        enemysPokemonLevel.setString("L. " + std::to_string(trainer->team[0]->getLevel()));
    }
    updateUI(player);
    window.draw(myHealthBarBox);
    window.draw(enemysHealthBarBox);
    window.draw(myHealthBar);
    window.draw(enemysHealthBar);
    window.draw(myPokemonName);
    window.draw(enemysPokemonName);
    window.draw(myPokemonLevel);
    window.draw(enemysPokemonLevel);
    window.draw(dialogBox);
    window.draw(battleLog);
}


void Battle::moveUp(Player& player){
    if(menuPageIndex != 2){
        menuButtons[abs(selectedItemIndex)%4].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        if(selectedItemIndex == -1)
            selectedItemIndex = 3;
        menuButtons[abs(selectedItemIndex)%4].setFillColor(sf::Color::Red);
    }else{
        menuButtons[abs(selectedItemIndex)%(player.team.size()-1)].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        if(selectedItemIndex == -1)
            selectedItemIndex = player.team.size() - 2;
        menuButtons[abs(selectedItemIndex)%(player.team.size()-1)].setFillColor(sf::Color::Red);
#ifdef DEBUG
        std::cout<<selectedItemIndex<<std::endl;
#endif
    }


}

void Battle::moveDown(Player& player) {
    if(menuPageIndex != 2){
        menuButtons[selectedItemIndex%4].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        if(selectedItemIndex == 4)
            selectedItemIndex = 0;
        menuButtons[selectedItemIndex%4].setFillColor(sf::Color::Red);
    }else{
        menuButtons[abs(selectedItemIndex)%(player.team.size()-1)].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        if(selectedItemIndex == player.team.size()-1)
            selectedItemIndex = 0;
        menuButtons[abs(selectedItemIndex)%(player.team.size()-1)].setFillColor(sf::Color::Red);
#ifdef DEBUG
        std::cout<<selectedItemIndex<<std::endl;
#endif
    }

}

void Battle::refreshMenu(Player& player) {
    if(menuPageIndex == 0){
        switch (selectedItemIndex){
            case 0:
                menuButtons[0].setString(player.team[0]->moves[0].getName());
                menuButtons[0].setScale(sf::Vector2f(0.3f,0.3f));
                menuButtons[1].setString(player.team[0]->moves[1].getName());
                menuButtons[1].setScale(sf::Vector2f(0.3f,0.3f));
                menuButtons[2].setString(player.team[0]->moves[2].getName());
                menuButtons[2].setScale(sf::Vector2f(0.3f,0.3f));
                menuButtons[3].setString(player.team[0]->moves[3].getName());
                menuButtons[3].setScale(sf::Vector2f(0.3f,0.3f));
                menuPageIndex = 1;
                break;
            case 1:
                //TODO swap pokemon
                for(int i = 0; i < 4;i++)
                    menuButtons[i].setString("");
                for (auto i : player.team)
                    std::cout<<i->getName()<<std::endl;
                switch (player.team.size()){
                    case 1:
                        battleLog.setString(player.team[0]->getName() + " is your only pokemon!");
                        menuPageIndex = 2;
                        resetMenu();
                        break;
                    case 6:
                        menuButtons[4].setString(player.team[5]->getName());
                        menuButtons[4].setScale(sf::Vector2f(0.3f,0.3f));
                        menuButtons[4].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 50));
                    case 5 :
                        menuButtons[3].setString(player.team[4]->getName());
                        menuButtons[3].setScale(sf::Vector2f(0.3f,0.3f));
                        menuButtons[3].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 40));
                    case 4 :
                        menuButtons[2].setString(player.team[3]->getName());
                        menuButtons[2].setScale(sf::Vector2f(0.3f,0.3f));
                        menuButtons[2].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 30));
                    case 3:
                        menuButtons[1].setString(player.team[2]->getName());
                        menuButtons[1].setScale(sf::Vector2f(0.3f,0.3f));
                        menuButtons[1].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 20));
                        menuButtons[1].setFillColor(sf::Color::Black);
                    case 2:
                        menuButtons[0].setString(player.team[1]->getName());
                        menuButtons[0].setScale(sf::Vector2f(0.3f,0.3f));
                        menuButtons[0].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 10));
                        menuButtons[0].setFillColor(sf::Color::Red);
                        selectedItemIndex = 0;
                        menuPageIndex = 2;
                        break;

                }

                break;
            case 2:
                if(trainer== nullptr){
                    if(player.catchPokemon(wildPokemon)){
                        Game::getInstance()->changeState(GameState::STATE_MAP);
                        Game::resetTimer();
#ifdef DEBUG
                        for(auto i:player.team)
                            std::cout<<i->getName()<<std::endl;
#endif
                    }
                }else{
                    battleLog.setString(" You can't catch "+trainer->getName()+"'s pokemon!");
                }

                break;
            case 3:
                if(trainer == nullptr){
                    battleLog.setString("Got away safely!");
                    delete wildPokemon;
                    Game::getInstance()->changeState(GameState::STATE_MAP);
                    Game::resetTimer();
                }else{
                    battleLog.setString("You can't run away!");
                }

                break;
        }
    }else if(menuPageIndex == 1){
        if(player.team[0]->moves[selectedItemIndex].getNUsage() > 0){
            haveYouSelectedAnAction = selectedItemIndex+1;
            resetMenu();
        }else{
            battleLog.setString("You can't use this move! Choose another one!");
        }

    }else if(menuPageIndex == 2){
        if(player.team[selectedItemIndex+1]->isAlive()){
            auto tmp = player.team[0];
            player.team[0] = player.team[selectedItemIndex+1];
            player.team[selectedItemIndex+1] = tmp;
            haveYouSwitchedYourPokemon = true;
        }else{
            battleLog.setString(player.team[selectedItemIndex+1]->getName() + " is dead...");
        }
        resetMenu();

    }
}

void Battle::resetMenu() {
    if(menuPageIndex!=0){
        menuButtons[0].setFont(font);
        menuButtons[0].setFillColor(sf::Color::Red);
        menuButtons[0].setString("FIGHT");
        menuButtons[0].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 10));
        menuButtons[0].setScale(0.6f, 0.6f);

        menuButtons[1].setFont(font);
        menuButtons[1].setFillColor(sf::Color::Black);
        menuButtons[1].setString("SWAP");
        menuButtons[1].setPosition(sf::Vector2f(menuBox.getPosition().x + 10, menuBox.getPosition().y + 50));
        menuButtons[1].setScale(0.6f, 0.6f);

        menuButtons[2].setFont(font);
        menuButtons[2].setFillColor(sf::Color::Black);
        menuButtons[2].setString("CATCH");
        menuButtons[2].setPosition(sf::Vector2f(menuBox.getPosition().x + 65, menuBox.getPosition().y + 10));
        menuButtons[2].setScale(0.6f, 0.6f);

        menuButtons[3].setFont(font);
        menuButtons[3].setFillColor(sf::Color::Black);
        menuButtons[3].setString("RUN");
        menuButtons[3].setPosition(sf::Vector2f(menuBox.getPosition().x + 65, menuBox.getPosition().y + 50));
        menuButtons[3].setScale(0.6f, 0.6f);

        menuButtons[4].setFont(font);
        menuButtons[4].setFillColor(sf::Color::Black);
        menuButtons[4].setString(" ");
        selectedItemIndex = 0;
        menuPageIndex=0;
#ifdef DEBUG
        std::cout<<"menu resetted"<<std::endl;
#endif
    }

}

void Battle::updateUI(Player& player) {
    myHealthBar.setSize(sf::Vector2f(80*player.team[0]->getCurrentHp()/player.team[0]->getMaxHp(),10.f));
    if(trainer == nullptr && wildPokemon != nullptr)
        enemysHealthBar.setSize(sf::Vector2f(80 * wildPokemon->getCurrentHp()/wildPokemon->getMaxHp(),10.f));
    else
        enemysHealthBar.setSize(sf::Vector2f(80 * trainer->team[0]->getCurrentHp()/trainer->team[0]->getMaxHp(),10.f));
}

void Battle::battleEngine(sf::RenderWindow &window, Player &player) {
    if(trainer == nullptr && wildPokemon != nullptr){ //battle against a wild Pokemon
        if(player.team[0]->isAlive() && wildPokemon->isAlive()){
//battle cycle
            draw(window, player);
            if(haveYouSelectedAnAction == 0 && !haveYouSwitchedYourPokemon){
            }else{
                //wildPokemon does a random move
                if(haveYouSwitchedYourPokemon){
                    wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0], window);
                }else {
                    if (player.team[0]->getSpeed() > wildPokemon->getSpeed()) {
                        //i go first
                        player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon,
                                               window);
                        if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                            //wildPokemon does a random move
                            wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0], window);
                        }
                    } else if (player.team[0]->getSpeed() < wildPokemon->getSpeed()) {
                        //wildPokemon goes first
                        wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0], window);
                        if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon,
                                                   window);
                        }

                    } else {
                        if (Dice::random(2) == 0) {
                            //i go first
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon,
                                                   window);
                            if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                                //wildPokemon does a random move
                                wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0], window);
                            }
                        } else {
                            wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0], window);
                            if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                                player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon,
                                                       window);
                            }

                        }
                    }
                }
                if(!player.team[0]->isAlive()) {
                    for(int i = 1; i < player.team.size(); i++){
                        if(player.team[i]->isAlive()){
                            auto tmp = player.team[0];
                            player.team[0] = player.team[i];
                            player.team[i] = tmp;
                        }
                    }
                }
                haveYouSelectedAnAction = 0;
                haveYouSwitchedYourPokemon = false;
            }

        }else{
            delete wildPokemon;
            Game::getInstance()->changeState(GameState::STATE_MAP);
            Game::resetTimer();
        }
    }else{ //battle against a trainer
        if(player.team[0]->isAlive() && trainer->team[0]->isAlive()){
//battle cycle
            draw(window, player);
            if(haveYouSelectedAnAction == 0 && !haveYouSwitchedYourPokemon){

            }else{
                //enemy does a random move
                if(haveYouSwitchedYourPokemon){
                    trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0], window);
                }else {
                    if (player.team[0]->getSpeed() > trainer->team[0]->getSpeed()) {
                        //i go first
                        player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *trainer->team[0],
                                               window);
                        if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                            //enemy does a random move
                            trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0], window);
                        }
                    } else if (player.team[0]->getSpeed() < trainer->team[0]->getSpeed()) {
                        //wildPokemon goes first
                        trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0], window);
                        if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                   *trainer->team[0], window);
                        }

                    } else {
                        if (Dice::random(2) == 0) {
                            //i go first
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                   *trainer->team[0], window);
                            if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                                //wildPokemon does a random move
                                trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0],
                                                         window);
                            }
                        } else {
                            trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0], window);
                            if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                                player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                       *trainer->team[0], window);
                            }
                        }
                    }
                }
                if(!player.team[0]->isAlive()) {
                    for(int i = 1; i < player.team.size(); i++){
                        if(player.team[i]->isAlive()){
                            auto tmp = player.team[0];
                            player.team[0] = player.team[i];
                            player.team[i] = tmp;
                        }
                    }
                }
                if(!trainer->team[0]->isAlive()) {
                    for(int i = 1; i < trainer->team.size(); i++){
                        if(trainer->team[i]->isAlive()){
                            auto tmp = trainer->team[0];
                            trainer->team[0] = trainer->team[i];
                            trainer->team[i] = tmp;
                        }
                    }
                }
                haveYouSelectedAnAction = 0;
                haveYouSwitchedYourPokemon = false;
            }

        }else{
            if(player.team[0]->isAlive()){
                //=> you have won
                player.winMoney(trainer);

            } else{
                trainer->winMoney(&player);

            }
            trainer = nullptr;
            Game::getInstance()->changeState(GameState::STATE_MAP);
            Game::resetTimer();
        }

    }

}

void Battle::setWildPokemon(Pokemon* pokemon) {
    wildPokemon = pokemon;
}

void Battle::setTrainer(Trainer* enemy){
    trainer = enemy;
}

void Battle::changeBattleLog(std::string msg) {
    battleLog.setString(msg);
}
