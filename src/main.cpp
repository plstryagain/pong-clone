#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "bat.hpp"
#include "ball.hpp"

inline static constexpr uint32_t SCREEN_WIDTH = 1920;
inline static constexpr uint32_t SCREEN_HEIGHT = 1080;
#ifdef __APPLE__
inline static constexpr uint32_t DPI_SCALE = 2;
#else
inline static constexpr uint32_t DPI_SCALE = 1;
#endif


int main() 
{
    sf::VideoMode vm{SCREEN_WIDTH * DPI_SCALE, SCREEN_HEIGHT * DPI_SCALE};
    sf::RenderWindow window{vm, "Pong", sf::Style::Fullscreen};
    int32_t score = 0;
    int32_t lives = 3;
    Bat bat{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 20};
    Ball ball{SCREEN_WIDTH / 2.0f, 0};
    sf::Text hud;
    sf::Font font;
    font.loadFromFile("assets/fonts/DS-DIGIT.TTF");
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20, 20);

    sf::Clock clock;
    while (window.isOpen()) {
        // process input
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            } 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                bat.moveLeft();
            } else {
                bat.stopLeft();
            }    
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                bat.moveRight();
            } else {
                bat.stopRight();
            }
        }

        // update
        sf::Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);

        std::stringstream ss;
        ss << "Score:" << score << " Lives:" << lives;
        hud.setString(ss.str());
        if (ball.getPosition().top > window.getSize().y) {
            ball.reboundBottom();
            --lives;
            if (lives < 1) {
                score = 0;
                lives = 3;
                ball.resetSpeed();
            }
        }
        if (ball.getPosition().top < 0) {
            ball.reboundBatOrTop();
            ++score;
        }

        if (ball.getPosition().left < 0 ||
            ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
            ball.reboundSides();
        }

        if (ball.getPosition().intersects(bat.getPosition())) {
            ball.reboundBatOrTop();
        }

        // render
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }
    return 0;
}