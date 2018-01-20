#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Snake.h"
#define ANCHO 1000
#define ALTO 600

using namespace sf;
using namespace std;

Texture t2;
void loadTextures();

Sprite red;
void loadSprites();

int main()
{
    RenderWindow window(VideoMode(ANCHO, ALTO), "Snake by jufergom");

    loadTextures();
    loadSprites();

    Snake snake;
    int timer = 0;

    int numbersX[50];
    int numbersY[30];


    for(int i = 0; i < 50; i++) {
        numbersX[i] = 20*i;
    }

    for(int i = 0; i < 30; i++) {
        numbersY[i] = 20*i;
    }

    int xRandom, yRandom;
    xRandom = numbersX[rand()%50+1];
    yRandom = numbersY[rand()%30+1];
    red.setPosition(xRandom, yRandom);

    Music gameplay;
    gameplay.openFromFile("music/bonus_room.wav");
    gameplay.setLoop(true);
    gameplay.setVolume(50);
    gameplay.play();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::A && snake.dx != 20) {
                    snake.dx = -20;
                    snake.dy = 0;
                }
                if(event.key.code == Keyboard::D && snake.dx != -20) {
                    snake.dx = 20;
                    snake.dy = 0;
                }
                if(event.key.code == Keyboard::W && snake.dy != 20) {
                    snake.dx = 0;
                    snake.dy = -20;
                }
                if(event.key.code == Keyboard::S && snake.dy != -20) {
                    snake.dx = 0;
                    snake.dy = 20;
                }
            }
        }

        //movimiento de la serpiente
        if(timer == 100) {
            snake.moveSnake();
            timer = 0;
        }
        timer++;

        //ver si la serpiente ha comido algo
        if(snake.colisionFood(red) && timer == 1) {
            snake.growUp();
            xRandom = numbersX[rand()%50+1];
            yRandom = numbersY[rand()%30+1];
            red.setPosition(xRandom, yRandom);
        }

        //Revisar si la serpiente muere
        snake.killSnake();
        if(!snake.alive)
            window.close();

        //dibujar cosas en el window
        window.clear();
        for(int i = 0; i < snake.squares.size(); i++) {
            window.draw(snake.squares[i]);
        }
        window.draw(red);
        window.display();
    }

    return 0;
}

void loadTextures() {
    t2.loadFromFile("images/red_square.png");
}

void loadSprites() {
    red.setTexture(t2);
}


