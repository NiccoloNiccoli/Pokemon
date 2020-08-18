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

//FIXME farlo meglio!!!!!

class BattleUIState;
enum class BattleUIStates;
class Battle {
public:
    Battle(Player& player);
    void draw(sf::RenderWindow& window, Player& player);
    void moveUp(Player& player);
    void moveDown(Player& player);
    void refreshMenu(Player& player);//Fixme find a better way to do it
    void resetMenu();
    void battleEngine(sf::RenderWindow& window, Player& player);//FIXME change its name

    static void setWildPokemon(Pokemon* pokemon);
    static void setTrainer(NPC* enemy);
    static void changeBattleLog(std::string msg);

    sf::Sprite background;
    sf::RectangleShape menuBox;
    sf::RectangleShape myHealthBarBox;
    sf::RectangleShape enemysHealthBarBox;
    sf::RectangleShape myHealthBar;
    sf::RectangleShape enemysHealthBar;
    sf::Text myPokemonName;
    sf::Text enemysPokemonName;
    sf::Text myPokemonLevel;
    sf::Text enemysPokemonLevel;
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
    static void changeFeedbackSentence();

    int getSentenceIndex() const;
    static void setSentenceIndex(int sentenceIndex);

    void escape();

private:

    void updateUI(Player& player);
    static Pokemon* wildPokemon;
    static NPC* trainer;
    int menuPageIndex = 1;
    //page 0 -> actions page 1 -> moves page 2 -> show team to change active pokemon
    static int selectedItemIndex;
    sf::Font font;

    const float scalingFactor = 1.78f;

    sf::Texture backgroundTexture;
    sf::Texture dialogBoxTexture;
    sf::Sprite dialogBox;
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

    sf::RectangleShape playersHPBar = sf::RectangleShape(sf::Vector2f(48 * scalingFactor,2*scalingFactor));
    sf::RectangleShape foesHPBar = sf::RectangleShape(sf::Vector2f(48 * scalingFactor, 2*scalingFactor));
    sf::RectangleShape playersEXPBar = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));
    sf::RectangleShape playersEXPBackground = sf::RectangleShape(sf::Vector2f(64*scalingFactor,2*scalingFactor));

    sf::Text menuButtons[4];
    sf::Text moveData[3];

    static int sentenceIndex;
    static sf::Text feedbackSentence;

    BattleUIState* UIstate = nullptr;


};

#endif //POKEMON_BATTLE_H
