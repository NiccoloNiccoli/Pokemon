//
// Created by Niccolò Niccoli on 11/08/2020.
//


#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture& spriteSheet, int widthOfSingleFrame, int heightOfSingleFrame,
                               int nFrames){
    rectangle = sf::IntRect(0,0,widthOfSingleFrame,heightOfSingleFrame);
    sprite = sf::Sprite(spriteSheet,rectangle);
    frames = nFrames - 1;
}

void AnimatedSprite::draw(sf::RenderWindow &window, int frequency, int row) {
    if(frequency == 0)
        frequency = 1;
    rectangle.top = rectangle.height * row;
    if(clock.getElapsedTime().asMilliseconds() >= 1000/frequency){
        if(rectangle.left == rectangle.width * frames){
            rectangle.left = 0;
        } else{
            rectangle.left += rectangle.width;
        }
        sprite.setTextureRect(rectangle);
        clock.restart();
    }
    window.draw(sprite);
}

void AnimatedSprite::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void AnimatedSprite::setPosition(float x, float y) {
    sprite.setPosition(x,y);
}

sf::Vector2f AnimatedSprite::getPosition() const {
    return sprite.getPosition();
}

sf::Rect<float> AnimatedSprite::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}

void AnimatedSprite::move(float x, float y) {
    sprite.move(x,y);
}

void AnimatedSprite::setScale(float factorX, float factorY) {
    sprite.setScale(factorX,factorY);
}

void AnimatedSprite::resetFrame() {
    rectangle.left = 0;
}



