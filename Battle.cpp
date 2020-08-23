//
// Created by Niccolò Niccoli on 25/06/2020.
//

#include <iostream>
#include <string>
#include <cmath>
#include "Battle.h"
#include "Player.h"
#include "Dice.h"


Pokemon* Battle::wildPokemon = nullptr;
NPC* Battle::trainer = nullptr;
sf::Text Battle::battleLog;
int Battle::selectedItemIndex = 0;
bool Battle::criticalHit = false;
bool Battle::notEffective = false;
bool Battle::superEffective = false;
bool Battle::firstMove = false;
Move* Battle::lastMoveUsed = new Move ("quick_attack");

Battle::Battle() {
    sf::RectangleShape tmpBox(sf::Vector2f(120.f, 100.f));
    tmpBox.setFillColor(sf::Color::White);
    tmpBox.setPosition(sf::Vector2f(300, 135));
    menuBox = tmpBox;
    if (!font.loadFromFile("../pkmnem.ttf")) {
        //TODO handle error
    }
    //initializing buttons "FIGHT", "SWAP", "CATCH", "RUN"
    resetMenu();

    //HP bar
   /* sf::RectangleShape tmpHpBox(sf::Vector2f(100, 40));
    tmpHpBox.setFillColor(sf::Color::White);
    myHealthBarBox = tmpHpBox;
    myHealthBarBox.setPosition(sf::Vector2f(0, 100));
    enemysHealthBarBox = tmpHpBox;
    enemysHealthBarBox.setPosition(sf::Vector2f(130, 5));
    sf::RectangleShape tmpHpBar(sf::Vector2f(80, 10));
    tmpHpBar.setFillColor(sf::Color::Green);
    myHealthBar = tmpHpBar;
    myHealthBar.setPosition(sf::Vector2f(5, 120));
    enemysHealthBar = tmpHpBar;
    enemysHealthBar.setPosition(sf::Vector2f(135, 25));*/



    sf::RectangleShape tmpDialogBox(sf::Vector2f(250.f, 40.f));
    tmpDialogBox.setFillColor(sf::Color::White);
    tmpDialogBox.setPosition(28.f, 190.f);
    _dialogBox = tmpDialogBox;
    battleLog.setFont(font);
    battleLog.setFillColor(sf::Color::Black);
    battleLog.setPosition(35.f, 195.f);
    battleLog.setScale(0.6f, 0.6f);
#ifdef DEBUG
    std::cout << "Battle created" << std::endl;
    resetMenu();
#endif
    if (!backgroundTexture.loadFromFile("../Textures/background.png")) {
        //TODO handle error
    }
    background.setTexture(backgroundTexture);
    background.setScale(1.f, (240 - 85.44) / 240);
    if (!dialogBoxTexture.loadFromFile("../Textures/dialogBox.png")) {
        //TODO
    }
    dialogBox.setTexture(dialogBoxTexture);
    dialogBox.setScale(scalingFactor, scalingFactor);
    dialogBox.setPosition(0.f, 240 - dialogBox.getGlobalBounds().height);
    if (!playersPlatformTexture.loadFromFile("../Textures/grassPlatformPlayer.png")) {
        //TODO
    }
    if (!foesPlatformTexture.loadFromFile("../Textures/grassPlatformEnemy.png")) {
        //TODO
    }
    if (!playersInfoBoxTexture.loadFromFile("../Textures/myHpBar.png")) {
        //TODO
    }
    if (!foesInfoBoxTexture.loadFromFile("../Textures/enemyHpBar.png")) {
        //TODO
    }
    playersPlatform.setTexture(playersPlatformTexture);
    playersPlatform.setScale(1.3f, 1.3f);
    playersPlatform.setPosition(0.f,
                                240 - dialogBox.getGlobalBounds().height - playersPlatform.getGlobalBounds().height);
    foesPlatform.setTexture(foesPlatformTexture);
    playersInfoBox.setTexture(playersInfoBoxTexture);
    foesInfoBox.setTexture(foesInfoBoxTexture);
    foesPlatform.setScale(1.3f, 1.3f);
    playersInfoBox.setScale(scalingFactor, scalingFactor);
    foesInfoBox.setScale(scalingFactor, scalingFactor);
    foesInfoBox.setPosition(10.f, 10.f);
    playersInfoBox.setPosition(1280 / 3 - playersInfoBox.getGlobalBounds().width - 10,
                               240 - dialogBox.getGlobalBounds().height - playersInfoBox.getGlobalBounds().height);
    foesPlatform.setPosition(1280 / 3 - foesPlatform.getGlobalBounds().width - 5,
                             240 - dialogBox.getGlobalBounds().height - playersInfoBox.getGlobalBounds().height -
                             foesPlatform.getGlobalBounds().height + 10);
    if (!actionBoxTexture.loadFromFile("../Textures/actionBox.png")) {
        //TODO
    }
    actionBox.setTexture(actionBoxTexture);
    if (!movesBoxTexture.loadFromFile("../Textures/movesBox.png")) {
        //TODO
    }
    movesBox.setTexture(movesBoxTexture);
    actionBox.setScale(scalingFactor, scalingFactor);
    actionBox.setPosition(1280 / 3 - actionBox.getGlobalBounds().width, 240 - actionBox.getGlobalBounds().height);
    movesBox.setScale(scalingFactor, scalingFactor);
    movesBox.setPosition(dialogBox.getPosition());
    playersHPBar.setFillColor(sf::Color::Green);
    playersHPBar.setPosition(playersInfoBox.getPosition().x + 48 * scalingFactor, playersInfoBox.getPosition().y + 17 * scalingFactor);
    playersHPBarBackground.setFillColor(sf::Color(100,100,100));
    playersHPBarBackground.setPosition(playersHPBar.getPosition());
    playersEXPBar.setFillColor(sf::Color(255,215,0)); //TODO find a better color
    playersEXPBar.setPosition(playersInfoBox.getPosition().x + 32 * scalingFactor, playersInfoBox.getPosition().y + 33 * scalingFactor);
    playersEXPBackground.setFillColor(sf::Color(70,70,70));
    playersEXPBackground.setPosition(playersEXPBar.getPosition());
    foesHPBar.setFillColor(sf::Color::Green);
    foesHPBar.setPosition(foesInfoBox.getPosition().x + 39 * scalingFactor, foesInfoBox.getPosition().y + 17 * scalingFactor);
    foesHPBarBackground.setFillColor(sf::Color(100,100,100));
    foesHPBarBackground.setPosition(foesHPBar.getPosition());
    for(int i = 0; i < 4; i++) {
        menuButtons[i].setFont(font);
        menuButtons[i].setFillColor(sf::Color::Black);
        menuButtons[i].setCharacterSize(20);
    }
    menuButtons[0].setFillColor(sf::Color::Red);
    for(int i = 0; i <3; i++){
        moveData[i].setFont(font);
        moveData[i].setFillColor(sf::Color::Black);
        moveData[i].setCharacterSize(20);
    }
    feedbackSentence.setFont(font);
    feedbackSentence.setFillColor(sf::Color::White);
    resetFeedbackSentencePosition();
    changeFeedbackSentence();
    myPokemonName.setFont(font);
    myPokemonName.setFillColor(sf::Color::Black);
    myPokemonName.setPosition(playersInfoBox.getPosition().x + 15 * scalingFactor, playersInfoBox.getPosition().y + 1 * scalingFactor );
    myPokemonName.setCharacterSize(20);
    myPokemonLevel.setFont(font);
    myPokemonLevel.setFillColor(sf::Color::Black);
    myPokemonLevel.setPosition( playersInfoBox.getPosition().x + playersInfoBox.getGlobalBounds().width - 14 * scalingFactor , myPokemonName.getPosition().y + 2 * scalingFactor);
    myPokemonLevel.setCharacterSize(17);
    enemysPokemonName.setFont(font);
    enemysPokemonName.setFillColor(sf::Color::Black);
    enemysPokemonName.setPosition(foesInfoBox.getPosition().x + 7 * scalingFactor, foesInfoBox.getPosition().y + 1 * scalingFactor );
    enemysPokemonName.setCharacterSize(20);
    enemysPokemonLevel.setFont(font);
    enemysPokemonLevel.setFillColor(sf::Color::Black);
    enemysPokemonLevel.setPosition(sf::Vector2f(foesInfoBox.getPosition().x + foesInfoBox.getGlobalBounds().width - 18.5 * scalingFactor , enemysPokemonName.getPosition().y + 2 * scalingFactor));
    enemysPokemonLevel.setCharacterSize(17);
    UIstate = new BattleUI_Scene0(this);
}

void Battle::draw(sf::RenderWindow &window, Player& player) {
    drawBackground(window);
    /*window.draw(menuBox);
    for(auto i : menuButtons)
        window.draw(i);
    player.team[0]->sprite.setPosition(10,130);
    player.team[0]->sprite.setScale(2.f,2.f);
    player.team[0]->draw(window, 2);
    myPokemonName.setString(player.team[0]->getName());
    myPokemonLevel.setString("L." + std::to_string(player.team[0]->getLevel()));
    if(trainer == nullptr && wildPokemon != nullptr){
        wildPokemon->sprite.setPosition(270,0);
        wildPokemon->sprite.setScale(1.5f,1.5f);
        wildPokemon->draw(window,0);
        enemysPokemonName.setString(wildPokemon->getName());
        enemysPokemonLevel.setString("L. " + std::to_string(wildPokemon->getLevel()));
    }else{
        trainer->team[0]->sprite.setPosition(270,0);
        trainer->team[0]->sprite.setScale(1.5f,1.5f);
        trainer->team[0]->draw(window,0);
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
    window.draw(_dialogBox);
    window.draw(battleLog);*/
    UIstate->draw(window);
}


void Battle::moveUp(Player& player){
    UIstate->moveUp(selectedItemIndex);
    /*
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
*/

}

void Battle::moveDown(Player& player) {
    UIstate->moveDown(selectedItemIndex);
   /* if(menuPageIndex != 2){
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
    }*/

}

void Battle::refreshMenu(Player& player) {/*
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

    }*/
    UIstate = UIstate->nextState(selectedItemIndex);
}

void Battle::resetMenu() {
   /* if(menuPageIndex!=0){
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
    }*/
   //FIXME
   if(dynamic_cast<BattleUI_ChooseAction*>(UIstate) || dynamic_cast<BattleUI_ChooseMove*>(UIstate) || dynamic_cast<BattleUI_ChoosePokemon*>(UIstate)) {
       BattleUIState *tmp;
       tmp = UIstate;
       UIstate = new BattleUI_ChooseAction(this);
       delete tmp;
   }else{
       std::cout<<"No"<<std::endl;
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
    draw(window,player);
    /*
    if(trainer == nullptr && wildPokemon != nullptr){ //battle against a wild Pokemon
        if(player.team[0]->isAlive() && wildPokemon->isAlive()){
//battle cycle
            draw(window, player);
            if(haveYouSelectedAnAction == 0 && !haveYouSwitchedYourPokemon){
            }else{
                //wildPokemon does a random move
                if(haveYouSwitchedYourPokemon){
                    wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0]);
                }else {
                    if (player.team[0]->getSpeed() > wildPokemon->getSpeed()) {
                        //i go first
                        player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon);
                        if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                            //wildPokemon does a random move
                            wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0]);
                        }
                    } else if (player.team[0]->getSpeed() < wildPokemon->getSpeed()) {
                        //wildPokemon goes first
                        wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0]);
                        if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon);
                        }

                    } else {
                        if (Dice::random(2) == 0) {
                            //i go first
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *wildPokemon);
                            if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                                //wildPokemon does a random move
                                wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0]);
                            }
                        } else {
                            wildPokemon->doMove(wildPokemon->moves[Dice::random(4)], *player.team[0]);
                            if (wildPokemon->isAlive() && player.team[0]->isAlive()) {
                                player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                       *wildPokemon);
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
            if(player.team[0]->isAlive()){
                player.team[0]->gainEXP(wildPokemon);
                delete wildPokemon;
                Game::getInstance()->changeState(GameState::STATE_MAP);
            }

            else{
                delete wildPokemon;
                Game::getInstance()->changeState(GameState::STATE_POKEMON_CENTER);
            }
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
                    trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0]);
                }else {
                    if (player.team[0]->getSpeed() > trainer->team[0]->getSpeed()) {
                        //i go first
                        player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1], *trainer->team[0]);
                        if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                            //enemy does a random move
                            trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0]);
                        }
                    } else if (player.team[0]->getSpeed() < trainer->team[0]->getSpeed()) {
                        //wildPokemon goes first
                        trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0]);
                        if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                   *trainer->team[0]);
                        }

                    } else {
                        if (Dice::random(2) == 0) {
                            //i go first
                            player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                   *trainer->team[0]);
                            if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                                //wildPokemon does a random move
                                trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0]);
                            }
                        } else {
                            trainer->team[0]->doMove(trainer->team[0]->moves[Dice::random(4)], *player.team[0]);
                            if (trainer->team[0]->isAlive() && player.team[0]->isAlive()) {
                                player.team[0]->doMove(player.team[0]->moves[haveYouSelectedAnAction - 1],
                                                       *trainer->team[0]);
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
                    player.team[0]->gainEXP(trainer->team[0]);
                }
                haveYouSelectedAnAction = 0;
                haveYouSwitchedYourPokemon = false;
            }

        }else{
            if(player.team[0]->isAlive()){
                //=> you have won
                player.winMoney(trainer);
                trainer = nullptr;
                Game::getInstance()->changeState(GameState::STATE_MAP);

            } else{
                trainer->winMoney(&player);
                trainer = nullptr;
                Game::getInstance()->changeState(GameState::STATE_POKEMON_CENTER);
            }
            Game::resetTimer();
        }

    }
*/
}

void Battle::setWildPokemon(Pokemon* pokemon) {
    wildPokemon = pokemon;
}

void Battle::setTrainer(NPC* enemy){
    trainer = enemy;
}

void Battle::changeBattleLog(std::string msg) {
    battleLog.setString(msg);
}

void Battle::drawBackground(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(foesPlatform);
    window.draw(playersPlatform);
}

void Battle::drawPlayersHPBar(sf::RenderWindow &window) {
    window.draw(playersHPBarBackground);
    window.draw(playersHPBar);
    window.draw(playersEXPBackground);
    window.draw(playersEXPBar);
    window.draw(playersInfoBox);
    window.draw(myPokemonName);
    window.draw(myPokemonLevel);
}

void Battle::drawFoesHPBar(sf::RenderWindow &window) {
    window.draw(foesHPBarBackground);
    window.draw(foesHPBar);
    window.draw(foesInfoBox);
    window.draw(enemysPokemonName);
    window.draw(enemysPokemonLevel);
}

void Battle::drawActionBox(sf::RenderWindow &window) {
    drawDialogBox(window);
    window.draw(actionBox);
    for(auto i : menuButtons)
        window.draw(i);
}

void Battle::drawMovesBox(sf::RenderWindow &window) {
    window.draw(movesBox);
    for(auto i : menuButtons)
        window.draw(i);
    for(auto i : moveData)
        window.draw(i);
}

void Battle::drawDialogBox(sf::RenderWindow &window) {
    window.draw(dialogBox);
}

void Battle::drawFeedbackSentence(sf::RenderWindow &window) {
    window.draw(feedbackSentence);
}


void Battle::setMenuButtonString(std::string string, int index) {
    menuButtons[index].setString(string);
}

void Battle::setMenuButtonPosition(BattleUIStates state) {
    if(state == BattleUIStates::CHOOSE_ACTION){
        menuButtons[0].setPosition(actionBox.getPosition().x + 15 * scalingFactor, actionBox.getPosition().y + 8 * scalingFactor);
        menuButtons[1].setPosition(menuButtons[0].getPosition().x,actionBox.getPosition().y + 28 * scalingFactor);
        menuButtons[2].setPosition(actionBox.getPosition().x + 71 * scalingFactor,menuButtons[0].getPosition().y);
        menuButtons[3].setPosition(menuButtons[2].getPosition().x, menuButtons[1].getPosition().y);
    }else if(state == BattleUIStates::CHOOSE_MOVE){
        menuButtons[0].setPosition(movesBox.getPosition().x + 11 * scalingFactor, movesBox.getPosition().y + 8 * scalingFactor);
        menuButtons[1].setPosition(menuButtons[0].getPosition().x, movesBox.getPosition().y  + 28 * scalingFactor);
        menuButtons[2].setPosition(movesBox.getPosition().x  + 90 * scalingFactor, menuButtons[0].getPosition().y);
        menuButtons[3].setPosition(menuButtons[2].getPosition().x, menuButtons[1].getPosition().y);
        moveData[0].setPosition(movesBox.getPosition().x + 201 * scalingFactor,movesBox.getPosition().y + 8 * scalingFactor);
        moveData[1].setPosition(movesBox.getPosition().x + 221 * scalingFactor,moveData[0].getPosition().y);
        moveData[2].setPosition(movesBox.getPosition().x + 194 * scalingFactor,movesBox.getPosition().y + 26 * scalingFactor);
    }
}

void Battle::setMoveDataString() {
    moveData[0].setString(std::to_string(Game::getInstance()->player.team[0]->moves[selectedItemIndex]->getNUsage()));
    moveData[1].setString(std::to_string(Game::getInstance()->player.team[0]->moves[selectedItemIndex]->getMaxUses()));
    moveData[2].setString(Game::getInstance()->player.team[0]->moves[selectedItemIndex]->getType().getTypeName());
}

void Battle::changeColorSelectedButton(sf::Color color) {
    for(int i = 0; i < 4; i++)
        menuButtons[i].setFillColor(sf::Color::Black);
    menuButtons[selectedItemIndex].setFillColor(color);
}

void Battle::changeFeedbackSentence() {
    std::string newSentence;
    if(trainer != nullptr){
        switch(sentenceIndex){
            case 0:
                newSentence = trainer->getName() + " would like to battle!";
                break;
            case 1:
                newSentence = trainer->getName() + " sent out " + trainer->team[0]->getName();
                break;
            case 2:
                newSentence = "Go " + Game::getInstance()->player.team[0]->getName();
                break;
            case 3:
                newSentence = "What will\n\n" + Game::getInstance()->player.team[0]->getName() + " do?";
                break;
            case 4:
                newSentence = Game::getInstance()->player.team[0]->getName() + " used " +
                              Game::getInstance()->player.team[0]->moves[selectedItemIndex]->getName();
                break;
            case 5:
                newSentence = "Critical hit!";
                break;
            case 6:
                newSentence = "It's not very effective!";
                break;
            case 7:
                newSentence = "It's super effective!";
                break;
            case -1:
                newSentence = "Missed!";
                break;
            case 9:
                newSentence = "Foe " + trainer->team[0]->getName() + " used "+ lastMoveUsed->getName();
                break;
            case 10:
                newSentence = Game::getInstance()->player.team[0]->getName() + " fainted!";
                break;
            case 11:
                newSentence = "Foe " + trainer->team[0]->getName() + " fainted!";
                break;
            case 12:
                levelInc = Game::getInstance()->player.team[0]->getLevel();
                expGained = Game::getInstance()->player.team[0]->gainEXP(trainer->team[0]);
                levelInc -= Game::getInstance()->player.team[0]->getLevel();
                levelInc *= -1;
                newSentence = Game::getInstance()->player.team[0]->getName() + " gained " + std::to_string(expGained) + " Exp.Points!";
                break;
            case 13:
                newSentence = Game::getInstance()->player.team[0]->getName() + " grew to Lv " +
                              myPokemonLevel.getString().toAnsiString();
                break;
            case 14:
                newSentence = "Choose your pokemon!";
                break;
            case 15:
                newSentence = Game::getInstance()->player.team[0]->getName() + ", good! Come back!";
                break;
            case 16:
                newSentence = Game::getInstance()->player.getName() + " defeated " + trainer->getName() + "!";
                break;
            case 17:
                newSentence = Game::getInstance()->player.getName() + " got " + std::to_string(Game::getInstance()->player.winMoney(trainer)) + " $ for winning!";
                break;
            case 18:
                sentenceIndex++;
            case 19:
                newSentence = "You can't run away!";
                break;
            case 20:
                sentenceIndex++;
            case 21:
                newSentence = "Foe " + trainer->team[0]->getName() + " can't be caught!";
                break;
            case 22:
                newSentence = Game::getInstance()->player.getName() + " has no more Pokemon left!";
                break;
            case 23:
                newSentence = Game::getInstance()->player.getName() + " gave " + std::to_string(trainer->winMoney(&Game::getInstance()->player)) +" $ to the winner...";
                break;
            case 24:
                newSentence = Game::getInstance()->player.getName() + " scurried  to a Pokemon Center,\n\nprotecting the exhausted and fainted Pokemon\n\nfrom further harm...";
                break;
            default:
                newSentence = "";
        }

    } else if(wildPokemon != nullptr){
        switch (sentenceIndex) {
            case 0:
                sentenceIndex = 1;
            case 1:
                newSentence = "Wild " + wildPokemon->getName() + " appeared!";
                break;
            case 2:
                newSentence = "Go " + Game::getInstance()->player.team[0]->getName();
                break;
            case 3:
                newSentence = "What will\n\n" + Game::getInstance()->player.team[0]->getName() + " do?";
                break;
            case 4:
                newSentence = Game::getInstance()->player.team[0]->getName() + " used " +
                              Game::getInstance()->player.team[0]->moves[selectedItemIndex]->getName();
                break;
            case 5:
                newSentence = "Critical hit!";
                break;
            case 6:
                newSentence = "It's not very effective!";
                break;
            case 7:
                newSentence = "It's super effective!";
                break;
            case -1:
                newSentence = "Missed!";
                break;
            case 9:
                newSentence = "Wild " + wildPokemon->getName() + " used " + lastMoveUsed->getName();
                break;
            case 10:
                newSentence = Game::getInstance()->player.team[0]->getName() + " fainted!";
                break;
            case 11:
                newSentence = "Wild " + wildPokemon->getName() + " fainted!";
                break;
            case 12:
                levelInc = Game::getInstance()->player.team[0]->getLevel();
                expGained = Game::getInstance()->player.team[0]->gainEXP(wildPokemon);
                levelInc -= Game::getInstance()->player.team[0]->getLevel();
                levelInc *= -1;
                newSentence = Game::getInstance()->player.team[0]->getName() + " gained " + std::to_string(expGained) + " Exp.Points!";
                break;
            case 13:
                newSentence = Game::getInstance()->player.team[0]->getName() + " grew to Lv " +
                              myPokemonLevel.getString().toAnsiString();
                break;
            case 14:
                newSentence = "Choose your pokemon!";
                break;
            case 15:
                newSentence = Game::getInstance()->player.team[0]->getName() + ", good! Come back!";
                break;
            case 16:
                newSentence =
                        Game::getInstance()->player.getName() + " defeated wild " + wildPokemon->getName() + "!";
                break;
            case 18:
                newSentence = "Got away safely!";
                break;
            case 19:
                newSentence = "You can't run away!";
                break;
            case 20:
                newSentence = "Wild " + wildPokemon->getName() + " was caught!";
                break;
            case 21:
                newSentence = "Argh! It was almost caught!";
                break;
            case 22:
                newSentence = Game::getInstance()->player.getName() + " has no more Pokemon left!";
                break;
            case 23:
                Game::getInstance()->player.setMoney(Game::getInstance()->player.getMoney()*0.9f);
                newSentence = Game::getInstance()->player.getName() + " dropped " + std::to_string(Game::getInstance()->player.getMoney()) +" $ in panic...";
                break;
            case 24:
                newSentence = Game::getInstance()->player.getName() + " scurried  to a Pokemon Center,\n\n protecting the exhausted and fainted Pokemon\n\nfrom further harm...";
                break;
            default:
                newSentence = "";
        }
    }


    feedbackSentence.setString(newSentence);
}

int Battle::getSentenceIndex() const {
    return sentenceIndex;
}

void Battle::setSentenceIndex(int _sentenceIndex) {
    sentenceIndex = _sentenceIndex;
}


void Battle::setFlags(bool crit, bool notEff, bool supEff) {
    criticalHit=crit;
    notEffective = notEff;
    superEffective = supEff;
}

bool Battle::isCriticalHit() {
    return criticalHit;
}

bool Battle::isNotEffective() {
    return notEffective;
}

bool Battle::isSuperEffective() {
    return superEffective;
}

bool Battle::amIFaster() {
    bool amIFaster = false;
    if(trainer != nullptr){
        if((Game::getInstance()->player.team[0]->getSpeed() > trainer->team[0]->getSpeed()) ||
        (Game::getInstance()->player.team[0]->getSpeed() == trainer->team[0]->getSpeed() && Dice::random(2) == 0))
            amIFaster = true;
    }else if(wildPokemon != nullptr){
        if((Game::getInstance()->player.team[0]->getSpeed() > wildPokemon->getSpeed()) ||
           (Game::getInstance()->player.team[0]->getSpeed() == wildPokemon->getSpeed() && Dice::random(2) == 0))
            amIFaster = true;
    }
    return amIFaster;
}

Pokemon *Battle::getWildPokemon() {
    return wildPokemon;
}

NPC *Battle::getTrainer() {
    return trainer;
}

sf::Vector2f Battle::getTrainerStandardPosition() {
    return sf::Vector2f(foesPlatform.getPosition().x + foesPlatform.getLocalBounds().width/2,
            foesPlatform.getPosition().y - foesPlatform.getLocalBounds().height/2 - 40);
}

void Battle::setUIState(BattleUIState *state) {
    BattleUIState *tmp = UIstate;
    UIstate = state;
    delete tmp;
}

sf::Vector2f Battle::getPlayerStandardPosition() {
    return sf::Vector2f(dialogBox.getPosition().x, dialogBox.getPosition().y - Game::getInstance()->player.inBattleSprite.getGlobalBounds().height);
}

void Battle::setMyPokemonData() {
    myPokemonLevel.setString(std::to_string(Game::getInstance()->player.team[0]->getLevel()));
    myPokemonName.setString(Game::getInstance()->player.team[0]->getName());
    playersEXPBar.setSize(sf::Vector2f(64 * scalingFactor *  ((pow(Game::getInstance()->player.team[0]->getLevel(),3) * 4/5 -
    Game::getInstance()->player.team[0]->getExpToNextLevel()))/(pow(Game::getInstance()->player.team[0]->getLevel(),3) * 4/5), 2 * scalingFactor));
}

void Battle::setEnemysPokemonData() {
    if (trainer != nullptr) {
        enemysPokemonLevel.setString(std::to_string(trainer->team[0]->getLevel()));
        enemysPokemonName.setString(trainer->team[0]->getName());
    }else if (wildPokemon!= nullptr){
        enemysPokemonLevel.setString(std::to_string(wildPokemon->getLevel()));
        enemysPokemonName.setString(wildPokemon->getName());
    }
}

Move* Battle::getLastMoveUsed() const {
    return lastMoveUsed;
}

void Battle::setLastMoveUsed(Move* lastMoveUsed) {
    Battle::lastMoveUsed = lastMoveUsed;
}

void Battle::updateHpBar(float x) {
    playersHPBar.setScale(x,1);
}

bool Battle::isFirstMove() {
    return firstMove;
}

void Battle::setFirstMove(bool isFirstMove) {
    Battle::firstMove = isFirstMove;
}

void Battle::setSelectedItemIndex(int selectedItemIndex) {
    Battle::selectedItemIndex = selectedItemIndex;
}

void Battle::resetButtons() {
    for(int i = 0; i < 4; i++) {
        menuButtons[i].setFillColor(sf::Color::Black);
    }
    selectedItemIndex = 0;
    menuButtons[0].setFillColor(sf::Color::Red);
}

int Battle::getLevelInc() {
    return levelInc;
}

void Battle::setLevelInc(int levelInc) {
    Battle::levelInc = levelInc;
}

void Battle::setExpGained(int expGained) {
    Battle::expGained = expGained;
}

int Battle::getExpGained() {
    return expGained;
}

void Battle::resetFeedbackSentencePosition() {
    feedbackSentence.setPosition(dialogBox.getPosition().x + 10 * scalingFactor, dialogBox.getPosition().y + 10 * scalingFactor);
}

