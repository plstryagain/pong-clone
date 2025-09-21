#include "ball.hpp"


Ball::Ball(float start_x, float start_y)
    : position_(start_x, start_y)
{
    shape_.setSize(sf::Vector2f{10, 10});
    shape_.setPosition(position_);
}

sf::FloatRect Ball::getPosition() const
{
    return shape_.getGlobalBounds();
}

sf::RectangleShape Ball::getShape() const
{
    return  shape_;
}


float Ball::getXVelocity() const
{
    return direction_x_;
}

void Ball::reboundSides()
{
    direction_x_ = -direction_x_;
}

void Ball::reboundBatOrTop()
{
    direction_y_ = -direction_y_;
    speed_ = speed_ * 1.1f;
}

void Ball::reboundBottom()
{
    position_.x = 0;
    position_.y = 500;
    direction_y_ = -direction_y_;
}

void Ball::resetSpeed()
{
    speed_ = 300.0f;
}

void Ball::update(sf::Time dt)
{
    position_.y += direction_y_ * speed_ * dt.asSeconds();
    position_.x += direction_x_ * speed_ * dt.asSeconds();
    shape_.setPosition(position_);
}