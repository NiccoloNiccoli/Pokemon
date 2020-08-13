//
// Created by Niccolò Niccoli on 11/08/2020.
//

#ifndef POKEMON_ANIMATEDSPRITE_H
#define POKEMON_ANIMATEDSPRITE_H


#include <SFML/Graphics.hpp>

class AnimatedSprite {
public:
    AnimatedSprite(sf::Texture& spriteSheet, int widthOfSingleFrame, int heightOfSingleFrame, int nFrames);
    void draw(sf::RenderWindow& window,int frequency=1, int row = 0);

    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::Rect<float> getGlobalBounds() const;
    void setScale(float factorX, float factorY);
    void move(float x, float y);

private:
    int frames;
    sf::IntRect rectangle;
   // sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock clock;
};


#endif //POKEMON_ANIMATEDSPRITE_H
