#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>

struct Snake {
    sf::Texture t1;
    std::vector<sf::Sprite> squares;
    float dx;
    float dy;
    bool alive;

    Snake();
    void moveSnake();
    void growUp();
    bool colisionFood(sf::Sprite);
    void killSnake();
};


#endif // SNAKE_H_INCLUDED
