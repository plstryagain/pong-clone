#pragma once

#include <SFML/Graphics.hpp>

class Bat
{
public:
    Bat(float start_x, float start_y);
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void update(sf::Time dt);

private:
    sf::Vector2f position_;
    sf::RectangleShape shape_;
    float speed_ = 1000.0f;
    bool moving_right_ = false;
    bool moving_left_ = false;
};