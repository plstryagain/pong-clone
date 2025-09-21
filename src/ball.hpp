#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics.hpp>

class Ball
{
public:
    Ball(float start_x, float start_y);

public:
    sf::FloatRect getPosition() const;
    sf::RectangleShape getShape() const;
    float getXVelocity() const;
    void reboundSides();
    void reboundBatOrTop();
    void reboundBottom();
    void resetSpeed();
    void update(sf::Time dt);

private:
    sf::Vector2f position_;
    sf::RectangleShape shape_;
    float speed_ = 300.0f;
    float direction_x_ = .2f;
    float direction_y_ = .2f;
};