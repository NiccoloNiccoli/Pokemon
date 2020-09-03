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
int Battle::selectedItemIndex = 0;
bool Battle::criticalHit = false;
bool Battle::notEffective = false;
bool Battle::superEffective = false;
bool Battle::firstMove = false;
Move* Battle::lastMoveUsed = new Move ("quick_attack");

Battle::Battle() {
    try {
        if (!font.loadFromFile("../pkmnem.ttf")) {
            throw std::runtime_error("File not found: ../pkmnem.ttf");
        }
        goBack();
        if (!backgroundTexture.loadFromFile("../Textures/background.png")) {
            throw std::runtime_error("File not found: ../Textures/background.png");
        }
        background.setTexture(backgroundTexture);
        background.setScale(1.f, (240 - 85.44) / 240);
        if (!dialogBoxTexture.loadFromFile("../Textures/dialogBox.png")) {
            throw std::runtime_error("File not found: ../Textures/dialogBox.png");
        }
        dialogBox.setTexture(dialogBoxTexture);
        dialogBox.setScale(scalingFactor, scalingFactor);
        dialogBox.setPosition(0.f, 240 - dialogBox.getGlobalBounds().height);
        if (!playersPlatformTexture.loadFromFile("../Textures/grassPlatformPlayer.png")) {
            throw std::runtime_error("File not found: ../Textures/grassPlatformPlayer.png");
        }
        if (!foesPlatformTexture.loadFromFile("../Textures/grassPlatformEnemy.png")) {
            throw std::runtime_error("File not found: ../Textures/grassPlatformEnemy.png");
        }
        if (!playersInfoBoxTexture.loadFromFile("../Textures/myHpBar.png")) {
            throw std::runtime_error("File not found: ../Textures/myHpBarBar.png");
        }
        if (!foesInfoBoxTexture.loadFromFile("../Textures/enemyHpBar.png")) {
            throw std::runtime_error("File not found: ../Textures/enemyHpBar.png");
        }
        playersPlatform.setTexture(playersPlatformTexture);
        playersPlatform.setScale(1.3f, 1.3f);
        playersPlatform.setPosition(0.f,
                                    240 - dialogBox.getGlobalBounds().height -
                                    playersPlatform.getGlobalBounds().height);
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
            throw std::runtime_error("File not found: ../Textures/actionsBox.png");
        }
        actionBox.setTexture(actionBoxTexture);
        if (!movesBoxTexture.loadFromFile("../Textures/movesBox.png")) {
            throw std::runtime_error("File not found: ../Textures/movesBox.png");
        }
        movesBox.setTexture(movesBoxTexture);
        actionBox.setScale(scalingFactor, scalingFactor);
        actionBox.setPosition(1280 / 3 - actionBox.getGlobalBounds().width, 240 - actionBox.getGlobalBounds().height);
        movesBox.setScale(scalingFactor, scalingFactor);
        movesBox.setPosition(dialogBox.getPosition());
        playersHPBar.setFillColor(sf::Color::Green);
        playersHPBar.setPosition(playersInfoBox.getPosition().x + 48 * scalingFactor,
                                 playersInfoBox.getPosition().y + 17 * scalingFactor);
        playersHPBarBackground.setFillColor(sf::Color(100, 100, 100));
        playersHPBarBackground.setPosition(playersHPBar.getPosition());
        playersEXPBar.setFillColor(sf::Color(255, 215, 0));
        playersEXPBar.setPosition(playersInfoBox.getPosition().x + 32 * scalingFactor,
                                  playersInfoBox.getPosition().y + 33 * scalingFactor);
        playersEXPBackground.setFillColor(sf::Color(70, 70, 70));
        playersEXPBackground.setPosition(playersEXPBar.getPosition());
        foesHPBar.setFillColor(sf::Color::Green);
        foesHPBar.setPosition(foesInfoBox.getPosition().x + 39 * scalingFactor,
                              foesInfoBox.getPosition().y + 17 * scalingFactor);
        foesHPBarBackground.setFillColor(sf::Color(100, 100, 100));
        foesHPBarBackground.setPosition(foesHPBar.getPosition());
        for (int i = 0; i < 4; i++) {
            menuButtons[i].setFont(font);
            menuButtons[i].setFillColor(sf::Color::Black);
            menuButtons[i].setCharacterSize(20);
        }
        menuButtons[0].setFillColor(sf::Color::Red);
        for (int i = 0; i < 3; i++) {
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
        myPokemonName.setPosition(playersInfoBox.getPosition().x + 15 * scalingFactor,
                                  playersInfoBox.getPosition().y + 1 * scalingFactor);
        myPokemonName.setCharacterSize(20);
        myPokemonLevel.setFont(font);
        myPokemonLevel.setFillColor(sf::Color::Black);
        myPokemonLevel.setPosition(
                playersInfoBox.getPosition().x + playersInfoBox.getGlobalBounds().width - 14 * scalingFactor,
                myPokemonName.getPosition().y + 2 * scalingFactor);
        myPokemonLevel.setCharacterSize(17);
        enemysPokemonName.setFont(font);
        enemysPokemonName.setFillColor(sf::Color::Black);
        enemysPokemonName.setPosition(foesInfoBox.getPosition().x + 7 * scalingFactor,
                                      foesInfoBox.getPosition().y + 1 * scalingFactor);
        enemysPokemonName.setCharacterSize(20);
        enemysPokemonLevel.setFont(font);
        enemysPokemonLevel.setFillColor(sf::Color::Black);
        enemysPokemonLevel.setPosition(
                sf::Vector2f(foesInfoBox.getPosition().x + foesInfoBox.getGlobalBounds().width - 18.5 * scalingFactor,
                             enemysPokemonName.getPosition().y + 2 * scalingFactor));
        enemysPokemonLevel.setCharacterSize(17);
        UIstate = new BattleUI_Init(this);
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
}

void Battle::draw(sf::RenderWindow &window) {
    drawBackground(window);
    UIstate->draw(window);
}


void Battle::moveUp() {
    UIstate->moveUp(selectedItemIndex);
}

void Battle::moveDown() {
    UIstate->moveDown(selectedItemIndex);
}

void Battle::goOn() {
    UIstate = UIstate->nextState(selectedItemIndex);
}

void Battle::goBack() {
   if(dynamic_cast<BattleUI_ChooseAction*>(UIstate) || dynamic_cast<BattleUI_ChooseMove*>(UIstate) || dynamic_cast<BattleUI_ChoosePokemon*>(UIstate)) {
       BattleUIState *tmp;
       tmp = UIstate;
       UIstate = new BattleUI_ChooseAction(this);
       delete tmp;
   }
}


void Battle::setWildPokemon(Pokemon* pokemon) {
    if(pokemon == nullptr){
        auto tmp = wildPokemon;
        wildPokemon = nullptr;
        delete tmp;
    }else
        wildPokemon = pokemon;
}

void Battle::setTrainer(NPC* enemy){
    trainer = enemy;
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


void Battle::setMenuButtonString(const std::string& string, int index) {
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
    moveData[0].setString(std::to_string(Game::getInstance()->player.team[0]->getMoves(selectedItemIndex)->getNUsage()));
    moveData[1].setString(std::to_string(Game::getInstance()->player.team[0]->getMoves(selectedItemIndex)->getMaxUses()));
    moveData[2].setString(Game::getInstance()->player.team[0]->getMoves(selectedItemIndex)->getType().getTypeName());
}

void Battle::changeColorSelectedButton(sf::Color color) {
    for(int i = 0; i < 4; i++)
        menuButtons[i].setFillColor(sf::Color::Black);
    menuButtons[selectedItemIndex].setFillColor(color);
}

void Battle::changeFeedbackSentence() {
    std::string newSentence;
        switch(sentenceIndex){
            case 0:
                if(trainer != nullptr) {
                    newSentence = trainer->getName() + " would like to battle!";
                }else if(wildPokemon != nullptr) {
                    sentenceIndex = 1;
                }
                break;
            case 1:
                if(trainer != nullptr) {
                    newSentence = trainer->getName() + " sent out " + trainer->team[0]->getName();
                }else if(wildPokemon != nullptr) {
                    newSentence = "Wild " + wildPokemon->getName() + " appeared!";
                }
                break;
            case 2:
                newSentence = "Go " + Game::getInstance()->player.team[0]->getName();
                break;
            case 3:
                newSentence = "What will\n\n" + Game::getInstance()->player.team[0]->getName() + " do?";
                break;
            case 4:
                newSentence = Game::getInstance()->player.team[0]->getName() + " used " +
                              Game::getInstance()->player.team[0]->getMoves(selectedItemIndex)->getName();
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
                if(trainer != nullptr) {
                    newSentence = "Foe " + trainer->team[0]->getName() + " used "+ lastMoveUsed->getName();
                }else if(wildPokemon != nullptr) {
                    newSentence = "Wild " + wildPokemon->getName() + " used " + lastMoveUsed->getName();
                }
                break;
            case 10:
                newSentence = Game::getInstance()->player.team[0]->getName() + " fainted!";
                break;
            case 11:
                if(trainer != nullptr) {
                    newSentence = "Foe " + trainer->team[0]->getName() + " fainted!";
                }else if(wildPokemon != nullptr) {
                    newSentence = "Wild " + wildPokemon->getName() + " fainted!";
                }
                break;
            case 12:
                levelInc = Game::getInstance()->player.team[0]->getLevel();
                if(trainer != nullptr) {
                    expGained = Game::getInstance()->player.team[0]->gainEXP(trainer->team[0]);
                }else if(wildPokemon != nullptr) {
                    expGained = Game::getInstance()->player.team[0]->gainEXP(wildPokemon);
                }
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
                //this sentence is not used
                newSentence = Game::getInstance()->player.team[0]->getName() + ", good! Come back!";
                break;
            case 16:
                if(trainer != nullptr) {
                    newSentence = Game::getInstance()->player.getName() + " defeated " + trainer->getName() + "!";
                }else if(wildPokemon != nullptr) {
                    newSentence = Game::getInstance()->player.getName() + " defeated wild " + wildPokemon->getName() + "!";
                }
                break;
            case 17:
                if(trainer != nullptr) {
                    newSentence = Game::getInstance()->player.getName() + " got " + std::to_string(Game::getInstance()->player.winMoney(trainer)) + " $ for winning!";
                }
                break;
            case 18:
                if(trainer != nullptr) {
                    sentenceIndex++;
                }else if(wildPokemon != nullptr) {
                    newSentence = "Got away safely!";
                    break;
                }
            case 19:
                newSentence = "You can't run away!";
                break;
            case 20:
                if(trainer != nullptr) {
                    sentenceIndex++;
                }else if(wildPokemon != nullptr) {
                    newSentence = "Wild " + wildPokemon->getName() + " was caught!";
                    break;
                }
            case 21:
                if(trainer != nullptr) {
                    newSentence = "Foe " + trainer->team[0]->getName() + " can't be caught!";
                }else if(wildPokemon != nullptr) {
                    newSentence = "Argh! It was almost caught!";
                }
                break;
            case 22:
                    newSentence = Game::getInstance()->player.getName() + " has no more Pokemon left!";
                break;
            case 23:
                if(trainer != nullptr) {
                    newSentence = Game::getInstance()->player.getName() + " gave " + std::to_string(trainer->winMoney(&(Game::getInstance()->player))) +" $ to the winner...";
                }else if(wildPokemon != nullptr) {
                    Game::getInstance()->player.setMoney(Game::getInstance()->player.getMoney()*0.9f);
                    newSentence = Game::getInstance()->player.getName() + " dropped " + std::to_string(Game::getInstance()->player.getMoney()) +" $ in panic...";
                }
                break;
            case 24:
                newSentence = Game::getInstance()->player.getName() + " scurried  to a Pokemon Center,\n\nprotecting the exhausted and fainted Pokemon\n\nfrom further harm...";
                break;
            default:
                newSentence = "";
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
    return sf::Vector2f(dialogBox.getPosition().x, dialogBox.getPosition().y - Game::getInstance()->player.getInBattleSpriteGlobalBounds().height);
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

void Battle::setLastMoveUsed(Move* _lastMoveUsed) {
    Battle::lastMoveUsed = _lastMoveUsed;
}

bool Battle::isFirstMove() {
    return firstMove;
}

void Battle::setFirstMove(bool isFirstMove) {
    Battle::firstMove = isFirstMove;
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

int Battle::getExpGained() {
    return expGained;
}

void Battle::resetFeedbackSentencePosition() {
    feedbackSentence.setPosition(dialogBox.getPosition().x + 10 * scalingFactor, dialogBox.getPosition().y + 10 * scalingFactor);
}

float Battle::getScalingFactor() const {
    return scalingFactor;
}

