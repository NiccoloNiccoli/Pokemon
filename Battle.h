//
// Created by Niccolò Niccoli on 25/06/2020.
//

#ifndef POKEMON_BATTLE_H
#define POKEMON_BATTLE_H
#include <SFML/Graphics.hpp>
#include "Trainer.h"
#include "Pokemon.h"
#include "Player.h"
#include "BattleUIStates.h"
#include "Game.h"

class BattleUIState;
enum class BattleUIStates;
class Battle {
public:
    Battle();
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    void goOn();
    void goBack();

    static void setWildPokemon(Pokemon* pokemon);
    static void setTrainer(NPC* enemy);
    static Pokemon *getWildPokemon();
    static NPC *getTrainer();

    void drawBackground(sf::RenderWindow& window);
    void drawPlayersHPBar(sf::RenderWindow& window);
    void drawFoesHPBar(sf::RenderWindow& window);
    void drawActionBox(sf::RenderWindow& window);
    void drawMovesBox(sf::RenderWindow& window);
    void drawDialogBox(sf::RenderWindow& window);
    void drawFeedbackSentence(sf::RenderWindow& window);
    void setMenuButtonString(const std::string& string, int index);
    void setMenuButtonPosition(BattleUIStates state);
    void setMoveDataString();
    void changeColorSelectedButton(sf::Color color);
    void changeFeedbackSentence();
    int getSentenceIndex() const;
    void setSentenceIndex(int sentenceIndex);
    void resetFeedbackSentencePosition();
    static void setFlags(bool crit, bool notEff, bool supEff);
    static bool isCriticalHit();
    static bool isNotEffective();
    static bool isSuperEffective();
    static bool isFirstMove();
    static void setFirstMove(bool isFirstMove);
    bool amIFaster();
    sf::Vector2f getTrainerStandardPosition();
    sf::Vector2f getPlayerStandardPosition();
    void setUIState(BattleUIState* state);
    void setMyPokemonData();
    void setEnemysPokemonData();
    Move* getLastMoveUsed() const;
    static void setLastMoveUsed(Move* lastMoveUsed);
    void resetButtons();
    float getScalingFactor() const;
    int getLevelInc();
    int getExpGained();
    sf::Text myPokemonLevel;
    sf::Sprite dialogBox;
    sf::Text feedbackSentence;
    sf::RectangleShape playersHPBar = sf::RectangleShape(sf::Vector2f(48 * scalingFactor,3*scalingFactor));
    sf::RectangleShape foesHPBar = sf::RectangleShape(sf::Vector2f(48 * scalingFactor, 3 *scalingFactor));
    sf::RectangleShape playersEXPBar = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));

private:

    static Pokemon* wildPokemon;
    static NPC* trainer;

    static int selectedItemIndex;
    sf::Text menuButtons[4];
    sf::Text moveData[3];

    const float scalingFactor = 1.78f;

    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture dialogBoxTexture;
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
    sf::Text myPokemonName;
    sf::Text enemysPokemonName;
    sf::Text enemysPokemonLevel;

    int sentenceIndex;

    static bool criticalHit, notEffective, superEffective, firstMove;
    static Move* lastMoveUsed;
    BattleUIState* UIstate = nullptr;
    int levelInc;
    int expGained;
};

#endif //POKEMON_BATTLE_H
