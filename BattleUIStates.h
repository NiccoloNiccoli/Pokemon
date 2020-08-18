//
// Created by Niccolò Niccoli on 17/08/2020.
//

#ifndef POKEMON_BATTLEUISTATES_H
#define POKEMON_BATTLEUISTATES_H


#include <SFML/Graphics.hpp>
#include "Battle.h"
class Battle;
enum class BattleUIStates{
    CHOOSE_ACTION,
    CHOOSE_POKEMON,
    CHOOSE_MOVE,
    UPDATE_MY_UI,
    BATTLE_INFO /*FIXME change name*/,
    UPDATE_FOES_UI
};
class BattleUIState{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual BattleUIState* nextState (int selectedItemIndex) = 0;
    virtual void moveUp(int& selectedItemIndex) = 0;
    virtual void moveDown(int& selectedItemIndex) = 0;

protected:
    Battle* battle;
};

class BattleUI_ChooseAction : public BattleUIState {
public:
    explicit BattleUI_ChooseAction(Battle* _battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex)override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};

class BattleUI_ChooseMove : public BattleUIState{
public:
    explicit BattleUI_ChooseMove(Battle* _battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex)override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
class BattleUI_FeedbackSentence /*FIXME find better name*/ : public BattleUIState{
public:
    explicit BattleUI_FeedbackSentence(Battle* _battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex)override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
#endif //POKEMON_BATTLEUISTATES_H
