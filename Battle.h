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
#include "BattleUIStates.h"
#include "Game.h"

//FIXME farlo meglio!!!!!
class BattleUIState;
enum class BattleUIStates;
class Battle {
public:
    Battle();
    void draw(sf::RenderWindow& window, Player& player);
    void moveUp(Player& player);
    void moveDown(Player& player);
    void refreshMenu(Player& player);//Fixme find a better way to do it
    void resetMenu();
    void battleEngine(sf::RenderWindow& window, Player& player);//FIXME change its name

    static void setWildPokemon(Pokemon* pokemon);
    static void setTrainer(NPC* enemy);
    static void changeBattleLog(std::string msg);


    sf::RectangleShape menuBox;
    sf::RectangleShape myHealthBarBox;
    sf::RectangleShape enemysHealthBarBox;
    sf::RectangleShape myHealthBar;
    sf::RectangleShape enemysHealthBar;
    sf::RectangleShape _dialogBox;
    static sf::Text battleLog;



    //FIXME
    int haveYouSelectedAnAction = 0;
    bool haveYouSwitchedYourPokemon = false;

    void drawBackground(sf::RenderWindow& window);
    void drawPlayersHPBar(sf::RenderWindow& window);
    void drawFoesHPBar(sf::RenderWindow& window);
    void drawActionBox(sf::RenderWindow& window);
    void drawMovesBox(sf::RenderWindow& window);
    void drawDialogBox(sf::RenderWindow& window);
    void drawFeedbackSentence(sf::RenderWindow& window);
    void setMenuButtonString(std::string string, int index);
    void setMenuButtonPosition(BattleUIStates state);
    void setMoveDataString();
    void changeColorSelectedButton(sf::Color color);
    void changeFeedbackSentence();

    int getSentenceIndex() const;
    void setSentenceIndex(int sentenceIndex);
    static void setFlags(bool crit, bool notEff, bool supEff);

    static bool isCriticalHit();

    static bool isNotEffective();

    static bool isSuperEffective();

    static bool isFirstMove();

    static void setFirstMove(bool isFirstMove);

    void escape();

    static Pokemon *getWildPokemon();

    static NPC *getTrainer();

    //FIXME - BATTLE METHODS - MAYBE PRIVATE(?)
    bool amIFaster();
    sf::Vector2f getTrainerStandardPosition();
    sf::Vector2f getPlayerStandardPosition();
    void setUIState(BattleUIState* state);
    void setMyPokemonData();
    void setEnemysPokemonData();

    Move* getLastMoveUsed() const;

    static void setLastMoveUsed(Move* lastMoveUsed);

    void updateHpBar(float x);

    void setSelectedItemIndex(int selectedItemIndex);
    void resetButtons();

    const float scalingFactor = 1.78f;

    sf::RectangleShape playersHPBar = sf::RectangleShape(sf::Vector2f(48 * scalingFactor,3*scalingFactor));
    sf::RectangleShape foesHPBar = sf::RectangleShape(sf::Vector2f(48 * scalingFactor, 3*scalingFactor));
    sf::RectangleShape playersEXPBar = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));

    int getLevelInc();

    int getExpGained();
    void setLevelInc(int levelInc);

    void setExpGained(int expGained);
    sf::Text myPokemonLevel;
    sf::Sprite dialogBox;
    sf::Text feedbackSentence;
    void resetFeedbackSentencePosition();

private:

    void updateUI(Player& player);
    static Pokemon* wildPokemon;
    static NPC* trainer;
    int menuPageIndex = 1;
    //page 0 -> actions page 1 -> moves page 2 -> show team to change active pokemon
    static int selectedItemIndex;
    sf::Font font;



    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture dialogBoxTexture;
   // sf::Sprite dialogBox;
    sf::Texture playersPlatformTexture;
    sf::Sprite playersPlatform;
    sf::Texture foesPlatformTexture;
    sf::Sprite foesPlatform;
    sf::Texture playersInfoBoxTexture;
    sf::Sprite playersInfoBox;
    sf::Texture foesInfoBoxTexture;
    sf::Sprite foesInfoBox;
    sf::Texture movesBoxTexture;
    sf::Sprite movesBox;
    sf::Texture actionBoxTexture;
    sf::Sprite actionBox;

    sf::RectangleShape playersHPBarBackground = sf::RectangleShape(sf::Vector2f(48 * scalingFactor,3*scalingFactor));
    sf::RectangleShape foesHPBarBackground = sf::RectangleShape(sf::Vector2f(48 * scalingFactor, 3*scalingFactor));
    sf::RectangleShape playersEXPBackground = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));
/*    sf::RectangleShape playersEXPBar = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));
    sf::RectangleShape playersEXPBackground = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));*/

    sf::Text myPokemonName;
    sf::Text enemysPokemonName;

    sf::Text enemysPokemonLevel;

    sf::Text menuButtons[4];
    sf::Text moveData[3];

    int sentenceIndex;

    static bool criticalHit, notEffective, superEffective, firstMove;
    static Move* lastMoveUsed;
    BattleUIState* UIstate = nullptr;
    int levelInc;
    int expGained;


};

#endif //POKEMON_BATTLE_H
