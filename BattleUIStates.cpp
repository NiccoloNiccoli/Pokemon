//
// Created by Niccolò Niccoli on 17/08/2020.
//

#include "BattleUIStates.h"
#include "Game.h"
#include "Dice.h"

BattleUI_ChooseAction::BattleUI_ChooseAction(Battle *_battle){
    battle = _battle;
    battle->setMenuButtonString("FIGHT",0);
    battle->setMenuButtonString("SWAP",1);
    battle->setMenuButtonString("CATCH",2);
    battle->setMenuButtonString("RUN",3);
    battle->setMenuButtonPosition(BattleUIStates::CHOOSE_ACTION);
    battle->setSentenceIndex(3);
    battle->changeFeedbackSentence();
}

void BattleUI_ChooseAction::draw(sf::RenderWindow &window) {
    battle->drawActionBox(window);
    battle->drawFoesHPBar(window);
    battle->drawPlayersHPBar(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState* BattleUI_ChooseAction::nextState(int selectedItemIndex) {
    BattleUIState* state = nullptr;
    switch(selectedItemIndex){
        case 0:
            state = new BattleUI_ChooseMove(battle);
            break;
        case 1:
            //state = new BattleUI_ChoosePokemon(battle);
            break;
        case 2:
            //TODO Catch
            break;
        case 3:
            if(Dice::random(9) > 1)
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
        battle->setMenuButtonString(Game::getInstance()->player.team[0]->moves[i].getName(),i);
    battle->setMoveDataString();
    battle->setMenuButtonPosition(BattleUIStates::CHOOSE_MOVE);
}

void BattleUI_ChooseMove::draw(sf::RenderWindow &window) {
    battle->drawPlayersHPBar(window);
    battle->drawFoesHPBar(window);
    battle->drawMovesBox(window);
}

BattleUIState *BattleUI_ChooseMove::nextState(int selectedItemIndex) {
    BattleUIState* state;
    switch(selectedItemIndex){
        case 0:
            state = new BattleUI_FeedbackSentence(battle);
                    //TODO textToBeDispayed.setString(pokemon.getName() + " used " + pokemon.move[selecteditem].getName())
            break;
        case 1:
            state = new BattleUI_FeedbackSentence(battle);
            break;
        case 2:
            state = new BattleUI_FeedbackSentence(battle);
            break;
        case 3:
            state = new BattleUI_FeedbackSentence(battle);
            break;
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
    battle->changeFeedbackSentence();
}


void BattleUI_FeedbackSentence::draw(sf::RenderWindow &window) {
    battle->drawDialogBox(window);
    battle->drawFoesHPBar(window);
    battle->drawPlayersHPBar(window);
    battle->drawFeedbackSentence(window);
}

BattleUIState *BattleUI_FeedbackSentence::nextState(int selectedItemIndex) {
    int sentenceIndex = battle->getSentenceIndex();
    BattleUIState* state ;
    switch(sentenceIndex){
        case 0:
            battle->setSentenceIndex(battle->getSentenceIndex()+1);
            state = new BattleUI_FeedbackSentence(battle);
            break;
        case 1:
            battle->setSentenceIndex(battle->getSentenceIndex()+1);
            state = new BattleUI_FeedbackSentence(battle);
            break;
        case 2:
            battle->setSentenceIndex(battle->getSentenceIndex()+1);
            state = new BattleUI_ChooseAction(battle);
            break;
        case 3:
           /* battle->setSentenceIndex(battle->getSentenceIndex()+1);
            state = new BattleUI_ChooseAction(battle);*/
            break;
        case 18:
            state = new BattleUI_FeedbackSentence(battle);
            battle->escape();
            break;
        case 19:
            state = new BattleUI_ChooseAction(battle);
            break;

    }
    return state;
}

void BattleUI_FeedbackSentence::moveUp(int &selectedItemIndex) {

}

void BattleUI_FeedbackSentence::moveDown(int &selectedItemIndex) {

}

