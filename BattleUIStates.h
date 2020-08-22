//
// Created by Niccolò Niccoli on 17/08/2020.
//

#ifndef POKEMON_BATTLEUISTATES_H
#define POKEMON_BATTLEUISTATES_H


#include <SFML/Graphics.hpp>
#include "Battle.h"
#include "Game.h"

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
private:
    int oldIndex = -1;
};
class BattleUI_Scene0 : public BattleUIState{
public:
    explicit BattleUI_Scene0(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
class BattleUI_Scene1 : public BattleUIState{
public:
    explicit BattleUI_Scene1(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
private:
    int oldIndex = 0;
};
class BattleUI_Scene2 : public BattleUIState{
public:
    explicit BattleUI_Scene2(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
private:
    int oldIndex = 0;
};
class BattleUI_MoveAnim : public BattleUIState{
public:
    explicit BattleUI_MoveAnim(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
class BattleUI_UpdateHpBars : public BattleUIState{
public:
    explicit BattleUI_UpdateHpBars(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
private:
    bool updatePlayersHpBar();
    bool updateEnemysHpBar();
    float oldPlayersHpBarLength;
    float oldEnemysHpBarLength;
    float newPlayersHpBarLength;
    float newEnemysHpBarLength;
    float step1 = 0.33f;
    float step2 = 0.33f;
};
class BattleUI_UpdateExpBar : public BattleUIState{
public:
    explicit BattleUI_UpdateExpBar(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
private:
    void updateExpBar();
    int lvlInc = 0;
    float oldExpGained;
    float expGained = 0;
    float step = 1.f;
};
class BattleUI_Victory : public BattleUIState{
public:
    explicit BattleUI_Victory(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};

class BattleUI_Defeat : public BattleUIState{
public:
    explicit BattleUI_Defeat(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
class BattleUI_OnlyPlayersPokemon : public BattleUIState{
public:
    explicit BattleUI_OnlyPlayersPokemon(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
class BattleUI_OnlyEnemysPokemon : public BattleUIState{
public:
    explicit BattleUI_OnlyEnemysPokemon(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
class BattleUI_ChoosePokemon : public BattleUIState{
public:
    explicit BattleUI_ChoosePokemon(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture redXTexture;
    sf::Sprite redX;
    sf::Texture cursorTexture;
    sf::Sprite cursor;
    sf::Vector2f originalSpritePosition;
    sf::RectangleShape hpBars[6];
    sf::RectangleShape hpBarsBackground [6];
    sf::Font font;
    sf::Text names[6];
    int selectedItem = 1;

};
class BattleUI_CatchPokemon : public BattleUIState{
public:
    explicit BattleUI_CatchPokemon(Battle *_battle);
    void draw(sf::RenderWindow& window) override;
    BattleUIState* nextState (int selectedItemIndex = 0) override;
    void moveUp(int& selectedItemIndex) override ;
    void moveDown(int& selectedItemIndex) override;
};
#endif //POKEMON_BATTLEUISTATES_H
