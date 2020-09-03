//
// Created by Niccolò Niccoli on 17/08/2020.
//

#include <iostream>
#include "BattleUIStates.h"
#include "Game.h"
#include "Dice.h"

BattleUI_ChooseAction::BattleUI_ChooseAction(Battle *_battle){
    battle = _battle;
    battle->resetButtons();
    battle->setMenuButtonString("FIGHT",0);
    battle->setMenuButtonString("SWAP",1);
    battle->setMenuButtonString("CATCH",2);
    battle->setMenuButtonString("RUN",3);
    battle->setMenuButtonPosition(BattleUIStates::CHOOSE_ACTION);
    battle->setSentenceIndex(3);
    battle->feedbackSentence.setPosition(battle->feedbackSentence.getPosition().x, battle->feedbackSentence.getPosition().y - 6 * battle->getScalingFactor());
    battle->feedbackSentence.setCharacterSize(27);
    battle->changeFeedbackSentence();
}

void BattleUI_ChooseAction::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr)
        battle->getTrainer()->team[0]->draw(window,0);
    else if(battle->getWildPokemon() != nullptr)
        battle->getWildPokemon()->draw(window,0);
    Game::getInstance()->player.team[0]->draw(window,2);
    battle->drawActionBox(window);
    battle->drawFoesHPBar(window);
    battle->drawPlayersHPBar(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState* BattleUI_ChooseAction::nextState(int selectedItemIndex) {
    battle->resetFeedbackSentencePosition();
    battle->feedbackSentence.setCharacterSize(30);
    BattleUIState* state = nullptr;
    bool isSomeoneAlive = false;
    switch(selectedItemIndex) {
        case 0:
            state = new BattleUI_ChooseMove(battle);
            break;
        case 1:
            for (int i = 1; i < Game::getInstance()->player.team.size(); i++) {
                if (Game::getInstance()->player.team[i]->isAlive())
                    isSomeoneAlive = true;
            }
            if (isSomeoneAlive)
                state = new BattleUI_ChoosePokemon(battle);
            else
                state = new BattleUI_ChooseAction(battle);
            break;
        case 2:
            if (Game::getInstance()->player.team.size() < 6 && battle->getWildPokemon() != nullptr &&
                battle->getTrainer() ==
                nullptr) {
                state = new BattleUI_CatchPokemon(battle);
            } else {
                state = new BattleUI_ChooseAction(battle);
            }
            break;
        case 3:
                if (Dice::random(10) > 1 && battle->getTrainer() == nullptr && battle->getWildPokemon() != nullptr)
                    battle->setSentenceIndex(18);
                else
                    battle->setSentenceIndex(19);
                state = new BattleUI_FeedbackSentence(battle);
            break;
    }
    return state;

}

void BattleUI_ChooseAction::moveUp(int& selectedItemIndex) {
    selectedItemIndex--;
    if(selectedItemIndex == -1)
        selectedItemIndex = 3;
    battle->changeColorSelectedButton(sf::Color::Red);
}

void BattleUI_ChooseAction::moveDown(int& selectedItemIndex) {
    selectedItemIndex++;
    if(selectedItemIndex == 4)
        selectedItemIndex = 0;
    battle->changeColorSelectedButton(sf::Color::Red);
}

BattleUI_ChooseMove::BattleUI_ChooseMove(Battle *_battle) {
    battle = _battle;
    for (int i = 0; i < 4; i++)
        battle->setMenuButtonString(Game::getInstance()->player.team[0]->getMoves(i)->getName(),i);
    battle->setMoveDataString();
    battle->setMenuButtonPosition(BattleUIStates::CHOOSE_MOVE);
}

void BattleUI_ChooseMove::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr)
        battle->getTrainer()->team[0]->draw(window,0);
    else if(battle->getWildPokemon() != nullptr)
        battle->getWildPokemon()->draw(window,0);
    Game::getInstance()->player.team[0]->draw(window,2);
    battle->drawPlayersHPBar(window);
    battle->drawFoesHPBar(window);
    battle->drawMovesBox(window);
}

BattleUIState *BattleUI_ChooseMove::nextState(int selectedItemIndex) {
    BattleUIState* state = nullptr;
    if(Game::getInstance()->player.team[0]->getMoves(selectedItemIndex)->getNUsage() > 0) {
        Battle::setFirstMove(true);
        if (battle->amIFaster()) {
            if (battle->getTrainer() != nullptr) {
                if (Game::getInstance()->player.team[0]->doMove(
                        Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getTrainer()->team[0])) != 0) {
                    battle->setSentenceIndex(4);
                    state = new BattleUI_MoveAnim(battle);
                }else{
                    battle->setSentenceIndex(-1);
                    state = new BattleUI_FeedbackSentence(battle);
                }
            }else if(battle->getWildPokemon() != nullptr){
                if (Game::getInstance()->player.team[0]->doMove(
                        Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getWildPokemon()))!= 0) {
                    battle->setSentenceIndex(4);
                    state = new BattleUI_MoveAnim(battle);
                }else{
                    battle->setSentenceIndex(-1);
                    state = new BattleUI_FeedbackSentence(battle);
                }
            }
        }else{
            if (battle->getTrainer() != nullptr) {
                if (battle->getTrainer()->team[0]->doMove(
                         battle->getTrainer()->team[0]->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                    battle->setSentenceIndex(9);
                    state = new BattleUI_MoveAnim(battle);
                }else{
                    battle->setSentenceIndex(-1);
                    state = new BattleUI_FeedbackSentence(battle);
                }
            }else if(battle->getWildPokemon() != nullptr){
                if (battle->getWildPokemon()->doMove(
                        battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                    battle->setSentenceIndex(9);
                    state = new BattleUI_MoveAnim(battle);
                }else{
                    battle->setSentenceIndex(-1);
                    state = new BattleUI_FeedbackSentence(battle);
                }
            }
        }
    }else{
        state = new BattleUI_ChooseMove(battle);
    }
    return state;

}

void BattleUI_ChooseMove::moveUp(int& selectedItemIndex) {
    selectedItemIndex--;
    if(selectedItemIndex == -1)
        selectedItemIndex = 3;
    battle->changeColorSelectedButton(sf::Color::Red);
    battle->setMoveDataString();
}

void BattleUI_ChooseMove::moveDown(int& selectedItemIndex) {
    selectedItemIndex++;
    if(selectedItemIndex == 4)
        selectedItemIndex = 0;
    battle->changeColorSelectedButton(sf::Color::Red);
    battle->setMoveDataString();
}

BattleUI_FeedbackSentence::BattleUI_FeedbackSentence(Battle *_battle) {
    battle = _battle;
    if(battle->getSentenceIndex() != -1 && battle->getSentenceIndex() != 18 && battle->getSentenceIndex() != 19) {
        if (battle->getSentenceIndex() % 4 == 0)
            oldIndex = 4;
        else if (battle->getSentenceIndex() % 9 == 0)
            oldIndex = 9;
        battle->setSentenceIndex(battle->getSentenceIndex() / oldIndex);
    }
    battle->changeFeedbackSentence();
    Game::resetTimer();
}


void BattleUI_FeedbackSentence::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr)
        battle->getTrainer()->team[0]->draw(window,0);
    else if(battle->getWildPokemon() != nullptr)
        battle->getWildPokemon()->draw(window,0);
    Game::getInstance()->player.team[0]->draw(window,2);
    battle->drawDialogBox(window);
    battle->drawFoesHPBar(window);
    battle->drawPlayersHPBar(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_FeedbackSentence::nextState(int selectedItemIndex) {
    int sentenceIndex = battle->getSentenceIndex();
    BattleUIState* state ;
    switch(sentenceIndex){
        case 5:
            if(battle->isNotEffective()) {
                battle->setSentenceIndex(6 * oldIndex);
                state = new BattleUI_FeedbackSentence(battle);
            }else if(battle->isSuperEffective()) {
                battle->setSentenceIndex(7 * oldIndex);
                state = new BattleUI_FeedbackSentence(battle);
            }else{
                sentenceIndex = oldIndex;
                if(Battle::isFirstMove()){
                    Battle::setFirstMove(false);
                        if(battle->getTrainer() != nullptr){
                            if(sentenceIndex == 4){
                                if(battle->getTrainer()->team[0]->isAlive()){
                                    if(Game::getInstance()->player.team[0]->isAlive()){
                                        if (battle->getTrainer()->team[0]->doMove(
                                                battle->getTrainer()->team[0]->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                                            battle->setSentenceIndex(9);
                                            state = new BattleUI_MoveAnim(battle);
                                        }else{
                                            battle->setSentenceIndex(-1);
                                            state = new BattleUI_FeedbackSentence(battle);
                                        }
                                    }else{
                                        battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                                    }
                                }else{
                                    battle->setSentenceIndex(11);
                                    state = new BattleUI_OnlyPlayersPokemon(battle);
                                }
                            }else if(sentenceIndex==9){
                                if(Game::getInstance()->player.team[0]->isAlive()) {
                                    if(battle->getTrainer()->team[0]->isAlive()){
                                        if (Game::getInstance()->player.team[0]->doMove(
                                                Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getTrainer()->team[0])) != 0) {
                                            battle->setSentenceIndex(4);
                                            state = new BattleUI_MoveAnim(battle);
                                        }else{
                                            battle->setSentenceIndex(-1);
                                            state = new BattleUI_FeedbackSentence(battle);
                                        }
                                    }else{
                                        battle->setSentenceIndex(11);
                                        state = new BattleUI_OnlyPlayersPokemon(battle);
                                    }
                                } else{
                                    battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                                }
                            }
                        }else if(battle->getWildPokemon() != nullptr){
                            if(sentenceIndex == 4){
                                if(battle->getWildPokemon()->isAlive()){
                                    if(Game::getInstance()->player.team[0]->isAlive()){
                                        if (battle->getWildPokemon()->doMove(
                                                battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                                            battle->setSentenceIndex(9);
                                            state = new BattleUI_MoveAnim(battle);
                                        }else{
                                            battle->setSentenceIndex(-1);
                                            state = new BattleUI_FeedbackSentence(battle);
                                        }
                                    }else{
                                        battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                                    }
                                }else{
                                    battle->setSentenceIndex(11);
                                    state = new BattleUI_OnlyPlayersPokemon(battle);
                                }
                            }else if(sentenceIndex==9){
                                if(Game::getInstance()->player.team[0]->isAlive()) {
                                    if(battle->getWildPokemon()->isAlive()){
                                        if (Game::getInstance()->player.team[0]->doMove(
                                                Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getWildPokemon()))!= 0) {
                                            battle->setSentenceIndex(4);
                                            state = new BattleUI_MoveAnim(battle);
                                        }else{
                                            battle->setSentenceIndex(-1);
                                            state = new BattleUI_FeedbackSentence(battle);
                                        }
                                    }else{
                                        battle->setSentenceIndex(11);
                                        state = new BattleUI_OnlyPlayersPokemon(battle);
                                    }
                                } else{
                                    battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                                }
                            }
                        }
                }else{
                    if(Game::getInstance()->player.team[0]->getCurrentHp() == 0){
                        battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                    }else if((battle->getTrainer() != nullptr && !battle->getTrainer()->team[0]->isAlive())||
                             (battle->getWildPokemon() != nullptr && !battle->getWildPokemon()->isAlive())){
                        battle->setSentenceIndex(11);
                        state = new BattleUI_OnlyPlayersPokemon(battle);
                    }else
                        state = new BattleUI_ChooseAction(battle);
                }
            }
            break;
        case 6:
        case 7:
        case -1:
            sentenceIndex = oldIndex;
            if(Battle::isFirstMove()){
                Battle::setFirstMove(false);
                if(battle->getTrainer() != nullptr){
                    if(sentenceIndex == 4 || sentenceIndex == -1){
                        if(battle->getTrainer()->team[0]->isAlive()){
                            if(Game::getInstance()->player.team[0]->isAlive()){
                                if (battle->getTrainer()->team[0]->doMove(
                                        battle->getTrainer()->team[0]->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                                    battle->setSentenceIndex(9);
                                    state = new BattleUI_MoveAnim(battle);
                                }else{
                                    battle->setSentenceIndex(-1);
                                    state = new BattleUI_FeedbackSentence(battle);
                                }
                            }else{
                                battle->setSentenceIndex(10);
                                state = new BattleUI_OnlyEnemysPokemon(battle);
                            }
                        }else{
                            battle->setSentenceIndex(11);
                            state = new BattleUI_OnlyPlayersPokemon(battle);
                        }
                    }else if(sentenceIndex==9 || sentenceIndex == -1){
                        if(Game::getInstance()->player.team[0]->isAlive()) {
                            if(battle->getTrainer()->team[0]->isAlive()){
                                if (Game::getInstance()->player.team[0]->doMove(
                                        Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getTrainer()->team[0])) != 0) {
                                    battle->setSentenceIndex(4);
                                    state = new BattleUI_MoveAnim(battle);
                                }else{
                                    battle->setSentenceIndex(-1);
                                    state = new BattleUI_FeedbackSentence(battle);
                                }
                            }else{
                                battle->setSentenceIndex(11);
                                state = new BattleUI_OnlyPlayersPokemon(battle);
                            }
                        } else{
                            battle->setSentenceIndex(10);
                            state = new BattleUI_OnlyEnemysPokemon(battle);
                        }
                    }
                }else if(battle->getWildPokemon() != nullptr){
                    if(sentenceIndex == 4 || sentenceIndex == -1){
                        if(battle->getWildPokemon()->isAlive()){
                            if(Game::getInstance()->player.team[0]->isAlive()){
                                if (battle->getWildPokemon()->doMove(
                                        battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                                    battle->setSentenceIndex(9);
                                    state = new BattleUI_MoveAnim(battle);
                                }else{
                                    battle->setSentenceIndex(-1);
                                    state = new BattleUI_FeedbackSentence(battle);
                                }
                            }else{
                                battle->setSentenceIndex(10);
                                state = new BattleUI_OnlyEnemysPokemon(battle);
                            }
                        }else{
                            battle->setSentenceIndex(11);
                            state = new BattleUI_OnlyPlayersPokemon(battle);
                        }
                    }else if(sentenceIndex==9 || sentenceIndex == -1){
                        if(Game::getInstance()->player.team[0]->isAlive()) {
                            if(battle->getWildPokemon()->isAlive()){
                                if (Game::getInstance()->player.team[0]->doMove(
                                        Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getWildPokemon()))!= 0) {
                                    battle->setSentenceIndex(4);
                                    state = new BattleUI_MoveAnim(battle);
                                }else{
                                    battle->setSentenceIndex(-1);
                                    state = new BattleUI_FeedbackSentence(battle);
                                }
                            }else{
                                battle->setSentenceIndex(11);
                                state = new BattleUI_OnlyPlayersPokemon(battle);
                            }
                        } else{
                            battle->setSentenceIndex(10);
                            state = new BattleUI_OnlyEnemysPokemon(battle);
                        }
                    }
                }
            }else{
                if(Game::getInstance()->player.team[0]->getCurrentHp() == 0){
                    battle->setSentenceIndex(10);
                    state = new BattleUI_OnlyEnemysPokemon(battle);
                }else if((battle->getTrainer() != nullptr && !battle->getTrainer()->team[0]->isAlive())||
                         (battle->getWildPokemon() != nullptr && !battle->getWildPokemon()->isAlive())){
                    battle->setSentenceIndex(11);
                    state = new BattleUI_OnlyPlayersPokemon(battle);
                }else
                    state = new BattleUI_ChooseAction(battle);
            }
        break;
        case 18:
               state = nullptr;
               battle->setWildPokemon(nullptr);
                Game::resetTimer();
                Game::getInstance()->changeState(GameState::STATE_MAP);
            break;
        case 19:
            if(battle->getTrainer() != nullptr) {
                state = new BattleUI_ChooseAction(battle);
            }else if(battle->getWildPokemon() != nullptr){
                battle->setFirstMove(false);
                if (battle->getWildPokemon()->doMove(
                        battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                    battle->setSentenceIndex(9);
                    state = new BattleUI_MoveAnim(battle);
                }else{
                    battle->setSentenceIndex(-1);
                    state = new BattleUI_FeedbackSentence(battle);
                }
            }
               break;
        default:
            state = new BattleUI_FeedbackSentence(battle);
    }
    return state;
}

void BattleUI_FeedbackSentence::moveUp(int &selectedItemIndex) {

}

void BattleUI_FeedbackSentence::moveDown(int &selectedItemIndex) {

}

BattleUI_Init::BattleUI_Init(Battle *_battle){
    battle = _battle;
    battle->setSentenceIndex(0);
    battle->changeFeedbackSentence();
    Game::resetTimer();

}


void BattleUI_Init::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr){
        battle->getTrainer()->drawInBattleSprite(window,1,0);
        battle->getTrainer()->setInBattleSpritePosition(battle->getTrainerStandardPosition());
    }else if(battle->getWildPokemon() != nullptr){
        battle->setUIState(nextState());
    }
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
   if(Game::getTime() > 2.f)
       battle->setUIState(nextState());
}

BattleUIState* BattleUI_Init::nextState(int selectedItemIndex) {
    return new BattleUI_FoeEnters(battle);
}

void BattleUI_Init::moveUp(int &selectedItemIndex) {}

void BattleUI_Init::moveDown(int &selectedItemIndex) {}

BattleUI_FoeEnters::BattleUI_FoeEnters(Battle *_battle) {
    battle = _battle;
    oldIndex = battle->getSentenceIndex();
    battle->setSentenceIndex(1);
    battle->changeFeedbackSentence();
    float newEnemysHpBarLength = 0.f;
    if(battle->getTrainer() != nullptr) {
        battle->getTrainer()->team[0]->setPosition(battle->getTrainerStandardPosition().x - 20, battle->getTrainerStandardPosition().y);
        newEnemysHpBarLength = 48 *battle->getScalingFactor() * battle->getTrainer()->team[0]->getCurrentHp() / battle->getTrainer()->team[0]->getMaxHp();
    }else if(battle->getWildPokemon() != nullptr){
        battle->getWildPokemon()->setPosition(battle->getTrainerStandardPosition().x - 20, battle->getTrainerStandardPosition().y);
        newEnemysHpBarLength = 48 *battle->getScalingFactor() *battle->getWildPokemon()->getCurrentHp() / battle->getWildPokemon()->getMaxHp();
    }

    battle->foesHPBar.setSize(sf::Vector2f(newEnemysHpBarLength, 3 * battle->getScalingFactor()));
    if(battle->foesHPBar.getSize().x < 48 *battle->getScalingFactor()/2) {
        if (battle->foesHPBar.getSize().x < 48 *battle->getScalingFactor() / 4)
            battle->foesHPBar.setFillColor(sf::Color::Red);
        else
            battle->foesHPBar.setFillColor(sf::Color::Yellow);
    }else
        battle->foesHPBar.setFillColor(sf::Color::Green);
    battle->setEnemysPokemonData();
    Game::resetTimer();
}

void BattleUI_FoeEnters::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr){
        battle->getTrainer()->team[0]->draw(window,0);
    }else if(battle->getWildPokemon() != nullptr){
        battle->getWildPokemon()->draw(window,0);
    }
    if(oldIndex != 0 && oldIndex != 1 ){
        Game::getInstance()->player.team[0]->draw(window,2);
    }
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
    if(Game::getTime() > 2.f)
        battle->setUIState(nextState());
}

BattleUIState* BattleUI_FoeEnters::nextState(int selectedItemIndex) {
    if(oldIndex == 0 || oldIndex == 1) {
        return new BattleUI_PlayersPokemonEnters(battle);
    }else{
        battle->setSentenceIndex(3);
        return new BattleUI_ChooseAction(battle);
    }
}

void BattleUI_FoeEnters::moveUp(int &selectedItemIndex) {}

void BattleUI_FoeEnters::moveDown(int &selectedItemIndex) {}

BattleUI_PlayersPokemonEnters::BattleUI_PlayersPokemonEnters(Battle *_battle) {
    battle = _battle;
    oldIndex = battle->getSentenceIndex();
    battle->setSentenceIndex(2);
    battle->changeFeedbackSentence();
    Game::getInstance()->player.setInBattleSpritePosition(battle->getPlayerStandardPosition());
    Game::getInstance()->player.team[0]->setPosition(battle->getPlayerStandardPosition().x + Game::getInstance()->player.getInBattleSpriteGlobalBounds().width/2,battle->dialogBox.getPosition().y
    - Game::getInstance()->player.team[0]->getGlobalBounds().height/1.4f);
    battle->playersHPBar.setSize(sf::Vector2f(48 *battle->getScalingFactor() * Game::getInstance()->player.team[0]->getCurrentHp() / Game::getInstance()->player.team[0]->getMaxHp(),3 * battle->getScalingFactor()));
    battle->setMyPokemonData();
    Game::resetTimer();
}

void BattleUI_PlayersPokemonEnters::draw(sf::RenderWindow &window) {
    int row = 1;
    if(battle->getTrainer() != nullptr){
        battle->getTrainer()->team[0]->draw(window,0);
    }else if(battle->getWildPokemon() != nullptr){
        battle->getWildPokemon()->draw(window,0);
    }
    if(Game::getTime() > 1.5f){
        row = 0;
        Game::getInstance()->player.team[0]->draw(window,2);
    }
    Game::getInstance()->player.drawInBattleSprite(window,3,row);
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
    if(Game::getTime() > 1.0f)
        battle->setUIState(nextState());
}

BattleUIState *BattleUI_PlayersPokemonEnters::nextState(int selectedItemIndex) {
    BattleUIState* state;
    if(oldIndex == 1 || !(battle->isFirstMove())) {
        battle->setSentenceIndex(3);
        state = new BattleUI_ChooseAction(battle);
        battle->playersHPBar.setSize(sf::Vector2f(48 *battle->getScalingFactor() * Game::getInstance()->player.team[0]->getCurrentHp() / Game::getInstance()->player.team[0]->getMaxHp(), battle->playersHPBar.getSize().y));
        if(battle->playersHPBar.getSize().x < 48 *battle->getScalingFactor() /2) {
            if (battle->playersHPBar.getSize().x < 48 *battle->getScalingFactor()  / 4)
                battle->playersHPBar.setFillColor(sf::Color::Red);
            else
                battle->playersHPBar.setFillColor(sf::Color::Yellow);
        } else
            battle->playersHPBar.setFillColor(sf::Color::Green);
    }else{
        battle->setFirstMove(false);
        if(battle->getTrainer() != nullptr) {
            if (battle->getTrainer()->team[0]->doMove(
                    battle->getTrainer()->team[0]->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0])) !=
                0) {
                battle->setSentenceIndex(9);
                state = new BattleUI_MoveAnim(battle);
            } else {
                battle->setSentenceIndex(-1);
                state = new BattleUI_FeedbackSentence(battle);
            }
        }else if (battle->getWildPokemon() != nullptr){
            if (battle->getWildPokemon()->doMove(
                    battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                battle->setSentenceIndex(9);
                state = new BattleUI_MoveAnim(battle);
            }else{
                battle->setSentenceIndex(-1);
                state = new BattleUI_FeedbackSentence(battle);
            }
        }
    }
    return state;
}

void BattleUI_PlayersPokemonEnters::moveUp(int &selectedItemIndex) {}

void BattleUI_PlayersPokemonEnters::moveDown(int &selectedItemIndex) {}

BattleUI_MoveAnim::BattleUI_MoveAnim(Battle *_battle) {
    battle = _battle;
    battle->changeFeedbackSentence();
    Game::resetTimer();
}

void BattleUI_MoveAnim::draw(sf::RenderWindow &window) {
    if(battle->getSentenceIndex() == 4){

        if(battle->getTrainer() != nullptr)
            battle->getTrainer()->team[0]->draw(window,0);
        else if(battle->getWildPokemon() != nullptr)
            battle->getWildPokemon()->draw(window,0);
        battle->getLastMoveUsed()->draw(window,0);
        Game::getInstance()->player.team[0]->draw(window,3);
    }else if(battle->getSentenceIndex() == 9){
        if(battle->getTrainer() != nullptr)
            battle->getTrainer()->team[0]->draw(window,1);
        else if(battle->getWildPokemon() != nullptr)
            battle->getWildPokemon()->draw(window,1);
        battle->getLastMoveUsed()->draw(window,1);
        Game::getInstance()->player.team[0]->draw(window,2);
    }
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
    if(Game::getTime() > 0.90f)
        battle->setUIState(nextState());

}

BattleUIState *BattleUI_MoveAnim::nextState(int selectedItemIndex) {
    battle->getLastMoveUsed()->resetAnim();
    return new BattleUI_UpdateHpBars(battle);
}

void BattleUI_MoveAnim::moveUp(int &selectedItemIndex) {}

void BattleUI_MoveAnim::moveDown(int &selectedItemIndex) {}

BattleUI_UpdateHpBars::BattleUI_UpdateHpBars(Battle *_battle) {
    battle = _battle;
    oldPlayersHpBarLength = 48 * battle->getScalingFactor();
    oldEnemysHpBarLength = 48 * battle->getScalingFactor();
    newPlayersHpBarLength = 48 *battle->getScalingFactor() * Game::getInstance()->player.team[0]->getCurrentHp() / Game::getInstance()->player.team[0]->getMaxHp();
    if(battle->getTrainer() != nullptr){
        newEnemysHpBarLength = 48 *battle->getScalingFactor() *battle->getTrainer()->team[0]->getCurrentHp() / battle->getTrainer()->team[0]->getMaxHp();
    }else if(battle->getWildPokemon() != nullptr){
        newEnemysHpBarLength = 48 *battle->getScalingFactor() *battle->getWildPokemon()->getCurrentHp() / battle->getWildPokemon()->getMaxHp();
    }
    if(newPlayersHpBarLength > battle->playersHPBar.getSize().x)
        step1 *= -1;
    if(newEnemysHpBarLength > battle->foesHPBar.getSize().x)
        step2 *= -1;
    Game::resetTimer();
}

void BattleUI_UpdateHpBars::draw(sf::RenderWindow &window) {
    if(battle->foesHPBar.getSize().x < oldEnemysHpBarLength/2) {
        if (battle->foesHPBar.getSize().x < oldEnemysHpBarLength / 4)
            battle->foesHPBar.setFillColor(sf::Color::Red);
        else
            battle->foesHPBar.setFillColor(sf::Color::Yellow);
    }else
        battle->foesHPBar.setFillColor(sf::Color::Green);
    if(battle->playersHPBar.getSize().x < oldPlayersHpBarLength/2) {
        if (battle->playersHPBar.getSize().x < oldPlayersHpBarLength / 4)
            battle->playersHPBar.setFillColor(sf::Color::Red);
        else
            battle->playersHPBar.setFillColor(sf::Color::Yellow);
    } else
        battle->playersHPBar.setFillColor(sf::Color::Green);

        if(battle->getTrainer() != nullptr)
            battle->getTrainer()->team[0]->draw(window,0);
        else if(battle->getWildPokemon() != nullptr)
            battle->getWildPokemon()->draw(window,0);
    Game::getInstance()->player.team[0]->draw(window,2);
    if(battle->getSentenceIndex() == 4){
        if(!updateEnemysHpBar()){
            updatePlayersHpBar();
            battle->drawPlayersHPBar(window);
        }
        battle->drawFoesHPBar(window);
    }else if (battle->getSentenceIndex() == 9){
        if(!updatePlayersHpBar()){
            updateEnemysHpBar();
            battle->drawFoesHPBar(window);
        }

        battle->drawPlayersHPBar(window);
    }
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);


}

BattleUIState *BattleUI_UpdateHpBars::nextState(int selectedItemIndex) {
    BattleUIState *state;
    if(abs(battle->playersHPBar.getSize().x - newPlayersHpBarLength) > 0){
            battle->playersHPBar.setSize(sf::Vector2f(newPlayersHpBarLength, 3 * battle->getScalingFactor()));
        if(battle->playersHPBar.getSize().x < oldPlayersHpBarLength/2) {
            if (battle->playersHPBar.getSize().x < oldPlayersHpBarLength / 4)
                battle->playersHPBar.setFillColor(sf::Color::Red);
            else
                battle->playersHPBar.setFillColor(sf::Color::Yellow);
        }
    }else{
        if(Game::getInstance()->player.team[0]->getCurrentHp() == 0)
            battle->playersHPBar.setSize(sf::Vector2f(0, battle->playersHPBar.getSize().y));
        else if(Game::getInstance()->player.team[0]->getCurrentHp() ==Game::getInstance()->player.team[0]->getMaxHp() )
            battle->playersHPBar.setSize(sf::Vector2f(oldPlayersHpBarLength,battle->playersHPBar.getSize().y));
    }
    if(abs(battle->foesHPBar.getSize().x - newEnemysHpBarLength) > 0){
        battle->foesHPBar.setSize(sf::Vector2f(newEnemysHpBarLength, battle->foesHPBar.getSize().y));
        if(battle->foesHPBar.getSize().x < oldEnemysHpBarLength/2) {
            if (battle->foesHPBar.getSize().x < oldEnemysHpBarLength / 4)
                battle->foesHPBar.setFillColor(sf::Color::Red);
            else
                battle->foesHPBar.setFillColor(sf::Color::Yellow);
        }else
            battle->foesHPBar.setFillColor(sf::Color::Green);

    }else{
        if(battle->getTrainer()!= nullptr) {
            if (battle->getTrainer()->team[0]->getCurrentHp() == 0)
                battle->foesHPBar.setSize(sf::Vector2f(0, battle->foesHPBar.getSize().y));
            else if (battle->getTrainer()->team[0]->getCurrentHp() == battle->getTrainer()->team[0]->getMaxHp())
                battle->foesHPBar.setSize(sf::Vector2f(oldEnemysHpBarLength, battle->foesHPBar.getSize().y));
        }else if(battle->getWildPokemon() != nullptr){
            if (battle->getWildPokemon()->getCurrentHp() == 0)
                battle->foesHPBar.setSize(sf::Vector2f(0, battle->foesHPBar.getSize().y));
            else if (battle->getWildPokemon()->getCurrentHp() == battle->getWildPokemon()->getMaxHp())
                battle->foesHPBar.setSize(sf::Vector2f(oldEnemysHpBarLength, battle->foesHPBar.getSize().y));
        }
    }

    int oldIndex = battle->getSentenceIndex();
    if (Battle::isCriticalHit()){
        battle->setSentenceIndex(5 * oldIndex);
        state = new BattleUI_FeedbackSentence(battle);
    } else if(Battle::isSuperEffective()){
            battle->setSentenceIndex(7 * oldIndex);
            state = new BattleUI_FeedbackSentence(battle);
        }else if(Battle::isNotEffective()){
            battle->setSentenceIndex(6 * oldIndex);
            state = new BattleUI_FeedbackSentence(battle);
        } else{
        if(Battle::isFirstMove()){
            Battle::setFirstMove(false);
         if(battle->getTrainer() != nullptr){
            if(oldIndex == 4){
                if(battle->getTrainer()->team[0]->isAlive()){
                    if(Game::getInstance()->player.team[0]->isAlive()){
                        if (battle->getTrainer()->team[0]->doMove(
                                battle->getTrainer()->team[0]->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                            battle->setSentenceIndex(9);
                            state = new BattleUI_MoveAnim(battle);
                        }else{
                            battle->setSentenceIndex(-1);
                            state = new BattleUI_FeedbackSentence(battle);
                        }
                    }else{
                        battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);

                    }
                }else{
                 battle->setSentenceIndex(11);
                    state = new BattleUI_OnlyPlayersPokemon(battle);
                }
            }else if(oldIndex==9){
                if(Game::getInstance()->player.team[0]->isAlive()) {
                    if(battle->getTrainer()->team[0]->isAlive()){
                        if (Game::getInstance()->player.team[0]->doMove(
                                Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getTrainer()->team[0])) != 0) {
                            battle->setSentenceIndex(4);
                            state = new BattleUI_MoveAnim(battle);
                        }else{
                            battle->setSentenceIndex(-1);
                            state = new BattleUI_FeedbackSentence(battle);
                        }
                    }else{
                     battle->setSentenceIndex(11);
                     state = new BattleUI_OnlyPlayersPokemon(battle);
                    }
                } else{
                    battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                }
            }
        }else if(battle->getWildPokemon() != nullptr){
            if(oldIndex == 4){
                if(battle->getWildPokemon()->isAlive()){
                    if(Game::getInstance()->player.team[0]->isAlive()){
                        if (battle->getWildPokemon()->doMove(
                                battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
                            battle->setSentenceIndex(9);
                            state = new BattleUI_MoveAnim(battle);
                        }else{
                            battle->setSentenceIndex(-1);
                            state = new BattleUI_FeedbackSentence(battle);
                        }
                    }else{
                        battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                    }
                }else{
                 battle->setSentenceIndex(11);
                 state = new BattleUI_OnlyPlayersPokemon(battle);
                }
            }else if(oldIndex==9){
                if(Game::getInstance()->player.team[0]->isAlive()) {
                    if(battle->getWildPokemon()->isAlive()){
                        if (Game::getInstance()->player.team[0]->doMove(
                                Game::getInstance()->player.team[0]->getMoves(selectedItemIndex), *(battle->getWildPokemon()))!= 0) {
                            battle->setSentenceIndex(4);
                            state = new BattleUI_MoveAnim(battle);
                        }else{
                            battle->setSentenceIndex(-1);
                            state = new BattleUI_FeedbackSentence(battle);
                        }
                    }else{
                        battle->setSentenceIndex(11);
                        state = new BattleUI_OnlyPlayersPokemon(battle);
                    }
                } else{
                    battle->setSentenceIndex(10);
                        state = new BattleUI_OnlyEnemysPokemon(battle);
                }
            }
        }
    }else{
            if(Game::getInstance()->player.team[0]->getCurrentHp() == 0){
                battle->setSentenceIndex(10);
                state = new BattleUI_OnlyEnemysPokemon(battle);
            }else if((battle->getTrainer() != nullptr && !battle->getTrainer()->team[0]->isAlive())||
          (battle->getWildPokemon() != nullptr && !battle->getWildPokemon()->isAlive())){
                battle->setSentenceIndex(11);
                state = new BattleUI_OnlyPlayersPokemon(battle);
            }else
            state = new BattleUI_ChooseAction(battle);
        }
    }

   /* */
    return state;
}

void BattleUI_UpdateHpBars::moveUp(int &selectedItemIndex) {}

void BattleUI_UpdateHpBars::moveDown(int &selectedItemIndex) {}

bool BattleUI_UpdateHpBars::updatePlayersHpBar() {
    bool value = false;
    if(abs(battle->playersHPBar.getSize().x - newPlayersHpBarLength) > 0) {
            battle->playersHPBar.setSize(sf::Vector2f(battle->playersHPBar.getSize().x - step1, 3 * battle->getScalingFactor()));
        value = true;
    }else{
        if(Game::getInstance()->player.team[0]->getCurrentHp() == 0) {
            battle->playersHPBar.setSize(sf::Vector2f(0, battle->playersHPBar.getSize().y));
            value = true;
        }
        else if(Game::getInstance()->player.team[0]->getCurrentHp() ==Game::getInstance()->player.team[0]->getMaxHp() ) {
            battle->playersHPBar.setSize(sf::Vector2f(oldPlayersHpBarLength, battle->playersHPBar.getSize().y));
            value = true;
        }
    }
return value;
}

bool BattleUI_UpdateHpBars::updateEnemysHpBar() {
bool value = false;
    if(abs(battle->foesHPBar.getSize().x - newEnemysHpBarLength )> 0){
                battle->foesHPBar.setSize(
                        sf::Vector2f(battle->foesHPBar.getSize().x - step2, 3 * battle->getScalingFactor()));
        }else {
        if (battle->getTrainer() != nullptr) {
            if (battle->getTrainer()->team[0]->getCurrentHp() == 0)
                battle->foesHPBar.setSize(sf::Vector2f(0, battle->foesHPBar.getSize().y));
            else if (battle->getTrainer()->team[0]->getCurrentHp() == battle->getTrainer()->team[0]->getMaxHp())
                battle->foesHPBar.setSize(sf::Vector2f(oldEnemysHpBarLength, battle->foesHPBar.getSize().y));
        } else if (battle->getWildPokemon() != nullptr) {
            if (battle->getWildPokemon()->getCurrentHp() == 0)
                battle->foesHPBar.setSize(sf::Vector2f(0, battle->foesHPBar.getSize().y));
            else if (battle->getWildPokemon()->getCurrentHp() == battle->getWildPokemon()->getMaxHp())
                battle->foesHPBar.setSize(sf::Vector2f(oldEnemysHpBarLength, battle->foesHPBar.getSize().y));
        }

    }
    return value;
}

BattleUI_UpdateExpBar::BattleUI_UpdateExpBar(Battle *_battle) {
    battle = _battle;
    sf::Vector2f position = Game::getInstance()->player.team[0]->getPosition();
    battle->changeFeedbackSentence();
    lvlInc = battle->getLevelInc();
    oldExpGained = battle->playersEXPBar.getSize().x;
    expGained = 64 * battle->getScalingFactor() * battle->getExpGained()/((pow(Game::getInstance()->player.team[0]->getLevel(),3) * 4/5));
    Game::getInstance()->player.team[0]->setPosition(position.x, position.y);
    Game::resetTimer();
}

void BattleUI_UpdateExpBar::draw(sf::RenderWindow &window) {
    updateExpBar();
    Game::getInstance()->player.team[0]->draw(window,2);
    battle->drawPlayersHPBar(window);
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_UpdateExpBar::nextState(int selectedItemIndex) {
    battle->setSentenceIndex(16);
    BattleUIState* state = new BattleUI_Victory(battle);
    if(battle->getTrainer() != nullptr) {
        for (int i = 1; i < battle->getTrainer()->team.size(); i++) {
            if (battle->getTrainer()->team[i]->isAlive()) {
                auto tmp = battle->getTrainer()->team[0];
                battle->getTrainer()->team[0] = battle->getTrainer()->team[i];
                battle->getTrainer()->team[i]= tmp;
                state = new BattleUI_FoeEnters(battle);
            }
        }
    }
    return state;
}

void BattleUI_UpdateExpBar::moveUp(int &selectedItemIndex) {}

void BattleUI_UpdateExpBar::moveDown(int &selectedItemIndex) {}

void BattleUI_UpdateExpBar::updateExpBar() {
        if(lvlInc == 0) {
            if (battle->playersEXPBar.getSize().x < oldExpGained + expGained) {
                battle->playersEXPBar.setSize(
                        sf::Vector2f(battle->playersEXPBar.getSize().x + step, battle->playersEXPBar.getSize().y));
            }
        }else{
            if(battle->playersEXPBar.getSize().x < 64 * battle->getScalingFactor()){
                battle->playersEXPBar.setSize(
                        sf::Vector2f(battle->playersEXPBar.getSize().x + step, battle->playersEXPBar.getSize().y));
            }else{
                lvlInc--;
                oldExpGained = 0;
                battle->myPokemonLevel.setString(std::to_string(std::stoi(battle->myPokemonLevel.getString().toAnsiString()) + 1));
                battle->setSentenceIndex(13);
                battle->changeFeedbackSentence();
                battle->playersEXPBar.setSize(sf::Vector2f(0,battle->playersEXPBar.getSize().y));
            }
        }
}

BattleUI_Victory::BattleUI_Victory(Battle *_battle) {
    battle = _battle;
    battle->changeFeedbackSentence();
    Game::resetTimer();
}

void BattleUI_Victory::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr)
        battle->getTrainer()->drawInBattleSprite(window,1,2);
    Game::getInstance()->player.team[0]->draw(window,2);
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_Victory::nextState(int selectedItemIndex) {
    BattleUIState* state = nullptr;
    if(battle->getSentenceIndex() == 16 && battle->getTrainer() != nullptr){
        battle->setSentenceIndex(17);
        state = new BattleUI_Victory(battle);
    }else{
        if(battle->getTrainer() != nullptr)
            battle->setTrainer(nullptr);
        else if(battle->getWildPokemon() != nullptr)
            battle->setWildPokemon(nullptr);
        Game::getInstance()->changeState(GameState::STATE_MAP);
    }
    return state;
}

void BattleUI_Victory::moveUp(int &selectedItemIndex) {}

void BattleUI_Victory::moveDown(int &selectedItemIndex) {}

BattleUI_OnlyPlayersPokemon::BattleUI_OnlyPlayersPokemon(Battle *_battle) {
battle = _battle;
battle->changeFeedbackSentence();
Game::resetTimer();
}

void BattleUI_OnlyPlayersPokemon::draw(sf::RenderWindow &window) {
    Game::getInstance()->player.team[0]->draw(window,2);
    battle->drawPlayersHPBar(window);
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_OnlyPlayersPokemon::nextState(int selectedItemIndex) {
    battle->setSentenceIndex(12);
    return new BattleUI_UpdateExpBar(battle);
}

void BattleUI_OnlyPlayersPokemon::moveUp(int &selectedItemIndex) {}

void BattleUI_OnlyPlayersPokemon::moveDown(int &selectedItemIndex) {}

BattleUI_OnlyEnemysPokemon::BattleUI_OnlyEnemysPokemon(Battle *_battle) {
    battle = _battle;
    battle->changeFeedbackSentence();
    Game::resetTimer();
}

void BattleUI_OnlyEnemysPokemon::draw(sf::RenderWindow &window) {
    if(battle->getTrainer() != nullptr){
        battle->getTrainer()->team[0]->draw(window,0);
    }else if(battle->getWildPokemon() != nullptr){
        battle->getWildPokemon()->draw(window,0);
    }
    battle->drawFoesHPBar(window);
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_OnlyEnemysPokemon::nextState(int selectedItemIndex) {
    BattleUIState* state;
    battle->setSentenceIndex(22);
    state = new BattleUI_Defeat(battle);
    for(int i = 1; i < Game::getInstance()->player.team.size(); i++) {
        if (Game::getInstance()->player.team[i]->isAlive()) {//I have at least one pokemon who is alive
            battle->setSentenceIndex(14);
            state = new BattleUI_ChoosePokemon(battle);
        }
    }
    return state;
}

void BattleUI_OnlyEnemysPokemon::moveUp(int &selectedItemIndex) {}

void BattleUI_OnlyEnemysPokemon::moveDown(int &selectedItemIndex) {}

BattleUI_Defeat::BattleUI_Defeat(Battle *_battle) {
battle = _battle;
battle->changeFeedbackSentence();
if(battle->getSentenceIndex() == 24) {
    battle->feedbackSentence.setPosition(10,
                                         720 / 6 - 50);
    battle->feedbackSentence.setCharacterSize(20);
}Game::resetTimer();
}

void BattleUI_Defeat::draw(sf::RenderWindow &window) {
    if(battle->getSentenceIndex() != 24){
        if(battle->getTrainer() != nullptr){
            battle->getTrainer()->team[0]->draw(window,0);
        }else if(battle->getWildPokemon() != nullptr){
            battle->getWildPokemon()->draw(window,0);
        }
        battle->drawDialogBox(window);
        battle->drawFeedbackSentence(window);
    }else{
        window.clear(sf::Color::Black);
        battle->drawFeedbackSentence(window);
    }
}

BattleUIState *BattleUI_Defeat::nextState(int selectedItemIndex) {
    BattleUIState *state = nullptr;
    if (battle->getSentenceIndex() != 24) {
        battle->setSentenceIndex(battle->getSentenceIndex() + 1);
        state = new BattleUI_Defeat(battle);
    }else{
        if(battle->getTrainer() != nullptr) {
                battle->getTrainer();
                battle->getTrainer()->healTeam();
            battle->setTrainer(nullptr);
        }else if(battle->getWildPokemon() != nullptr) {
            battle->setWildPokemon(nullptr);
        }
        battle->resetFeedbackSentencePosition();
        battle->feedbackSentence.setCharacterSize(30);
        Game::getInstance()->changeState(GameState::STATE_POKEMON_CENTER);
    }
    return state;
}

void BattleUI_Defeat::moveUp(int &selectedItemIndex) {}

void BattleUI_Defeat::moveDown(int &selectedItemIndex) {}

BattleUI_ChoosePokemon::BattleUI_ChoosePokemon(Battle *_battle) {
    try {
        battle = _battle;
        battle->changeFeedbackSentence();
        if (!backgroundTexture.loadFromFile("../Textures/choosePokemonMenu.png")) {
            throw std::runtime_error("File not found: ../Textures/choosePokemonMenu.png");
        }
        background.setTexture(backgroundTexture);
        if (!font.loadFromFile("../pkmnem.ttf")) {
            throw std::runtime_error("File not found: ../pkmnem.ttf");
        }
    }catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
        for (int i = 0; i < Game::getInstance()->player.team.size(); i++) {
            names[i].setFont(font);
            names[i].setCharacterSize(20);
            names[i].setScale(0.9f, 0.9f);
            names[i].setFillColor(sf::Color::Black);
            if (i == 0) {
                names[i].setPosition(25, 75);
                names[i].setString(Game::getInstance()->player.team[i]->getName() + " Lv" +
                                   std::to_string(Game::getInstance()->player.team[i]->getLevel()) + "\n\nHP: "
                                   + std::to_string(Game::getInstance()->player.team[i]->getCurrentHp()) + "/" +
                                   std::to_string(Game::getInstance()->player.team[i]->getMaxHp()));
            } else {
                names[i].setString(Game::getInstance()->player.team[i]->getName() + " Lv" +
                                   std::to_string(Game::getInstance()->player.team[i]->getLevel()) + " HP: "
                                   + std::to_string(Game::getInstance()->player.team[i]->getCurrentHp()) + "/" +
                                   std::to_string(Game::getInstance()->player.team[i]->getMaxHp()));
                names[i].setPosition(200, 35 * i + 3);
            }
        }
        int i = 1;
        while (!Game::getInstance()->player.team[i]->isAlive() && i < Game::getInstance()->player.team.size()) {
            i++;
        }
        names[i].setFillColor(sf::Color::Red);
        selectedItem = i;
    }

void BattleUI_ChoosePokemon::draw(sf::RenderWindow &window) {
    window.draw(background);
    for (int i = 0; i < Game::getInstance()->player.team.size(); i++) {
        window.draw(names[i]);
    }

}

BattleUIState *BattleUI_ChoosePokemon::nextState(int selectedItemIndex) {
    BattleUIState* state = nullptr;
    auto tmp = Game::getInstance()->player.team[0];
    Game::getInstance()->player.team[0] = Game::getInstance()->player.team[selectedItem];
    Game::getInstance()->player.team[selectedItem]= tmp;
    battle->setFirstMove(true);
    state = new BattleUI_PlayersPokemonEnters(battle);
    return state;
}

void BattleUI_ChoosePokemon::moveUp(int &selectedItemIndex) {
    do{
        selectedItem--;
        if (selectedItem == 0)
            selectedItem = 5;
        for (int i = 1; i < Game::getInstance()->player.team.size(); i++) {
            names[i].setFillColor(sf::Color::Black);
        }
        names[selectedItem].setFillColor(sf::Color::Red);
    } while (!Game::getInstance()->player.team[selectedItem]->isAlive());
}
void BattleUI_ChoosePokemon::moveDown(int &selectedItemIndex) {
    do{
    selectedItem++;
    if(selectedItem == 6)
        selectedItem = 1;
    for(int i = 1; i < Game::getInstance()->player.team.size();i++){
        names[i].setFillColor(sf::Color::Black);
    }
    names[selectedItem].setFillColor(sf::Color::Red);
    } while (!Game::getInstance()->player.team[selectedItem]->isAlive());
}

BattleUI_CatchPokemon::BattleUI_CatchPokemon(Battle *_battle) {
    battle =_battle;
    battle->setSentenceIndex(99);
    battle->changeFeedbackSentence();
    if(Game::getInstance()->player.catchPokemon(battle->getWildPokemon())){
        battle->setSentenceIndex(20);
    }else{
        battle->setSentenceIndex(21);
    }
    try {
        if (!animationTexture.loadFromFile("../Textures/ballThrown.png")) {
            throw std::runtime_error("File not found: ../Textures/ballThrown.png");
        }
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
    Game::resetTimer();
}

void BattleUI_CatchPokemon::draw(sf::RenderWindow &window) {
    Game::getInstance()->player.team[0]->draw(window,2);
    if(Game::getTime() < 0.50f){
        animation.draw(window,12,0);
        battle->getWildPokemon()->draw(window,0);
    }else{
        battle->changeFeedbackSentence();
        if(battle->getSentenceIndex() == 20){
        }else{
            battle->getWildPokemon()->draw(window,0);
        }
    }
    battle->drawDialogBox(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_CatchPokemon::nextState(int selectedItemIndex) {
    BattleUIState* state = nullptr;
    while(Game::getTime() < 1){
        //just wait
    }
    if(battle->getSentenceIndex() == 20){
        Game::getInstance()->changeState(GameState::STATE_MAP);
    }else{
        if (battle->getWildPokemon()->doMove(
                battle->getWildPokemon()->getMoves(Dice::random(4)), *(Game::getInstance()->player.team[0]))!= 0) {
            battle->setSentenceIndex(9);
            state = new BattleUI_MoveAnim(battle);
        }else{
            battle->setSentenceIndex(-1);
            state = new BattleUI_FeedbackSentence(battle);
        }
    }
    return state;
}

void BattleUI_CatchPokemon::moveUp(int &selectedItemIndex) {}
void BattleUI_CatchPokemon::moveDown(int &selectedItemIndex) {}

