#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Snake.h"
#define ANCHO 1000
#define ALTO 600

using namespace sf;
using namespace std;

Texture t2;
void loadTextures();

Sprite red;
void loadSprites();

void game(RenderWindow *window, int numbersX[], int numbersY[]);

int main()
{
    RenderWindow window(VideoMode(ANCHO, ALTO), "Snake by jufergom");
    //todo esto formara parte del menu
    Texture menuTexture;
    menuTexture.loadFromFile("images/snake.jpg");
    Sprite menuSprite;
    menuSprite.setTexture(menuTexture);
    menuSprite.setPosition(150, 50);
    Font font;
    font.loadFromFile("fonts/orange_juice.ttf");
    Text texts[2];
    for(int i = 0; i < 2; i++) {
        texts[i].setFont(font);
        texts[i].setCharacterSize(50);
        texts[i].setColor(Color::Green);
    }
    texts[0].setString("Jugar");
    texts[0].setPosition(500-30, 400);
    texts[1].setString("Salir");
    texts[1].setPosition(500-30, 460);

    //esto manejara si se quiere acceder a la opcion de jugar
    int option = 0;

    loadTextures();
    loadSprites();

    //los posibles numeros aleatorios en donde puede salir la comida
    int numbersX[50];
    int numbersY[30];

    //se asignan las posibles coordenadas en los arrays
    for(int i = 0; i < 50; i++) {
        numbersX[i] = 20*i;
    }

    for(int i = 0; i < 30; i++) {
        numbersY[i] = 20*i;
    }

    //musica del menu
    Music menuMusic;
    menuMusic.openFromFile("music/title_theme.ogg");
    menuMusic.setLoop(true);
    menuMusic.setVolume(50);
    menuMusic.play();

    while (window.isOpen())
    {
        if(menuMusic.getStatus() == Music::Stopped) {
            menuMusic.play();
        }
        Event event;
        Vector2i mousePos = Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //cambio de color en las letras del menu
            for(int i = 0; i < 2; i++) {
                if(texts[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    texts[i].setColor(Color::Blue);
                }
                else {
                    texts[i].setColor(Color::Green);
                }
            }
            if(event.type == Event::MouseButtonPressed) {
                if(texts[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(event.key.code == Mouse::Left)  {
                        option = 1;
                    }
                }
                if(texts[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(event.key.code == Mouse::Left)  {
                        window.close();
                    }
                }
            }
            switch(option) {
                case 1: {
                    menuMusic.stop();
                    game(&window, numbersX, numbersY);
                    option = 0;
                    break;
                }
            }
        window.clear();
        window.draw(menuSprite);
        for(int i = 0; i < 2; i++)
            window.draw(texts[i]);
        window.display();
        }
    }
    return 0;
}

void loadTextures() {
    t2.loadFromFile("images/red_square.png");
}

void loadSprites() {
    red.setTexture(t2);
}

void game(RenderWindow *window, int numbersX[], int numbersY[]) {
    Event event;
    Snake snake;
    int movementTimer = 0;
    int xRandom, yRandom;
    xRandom = numbersX[rand()%50+1];
    yRandom = numbersY[rand()%30+1];
    red.setPosition(xRandom, yRandom);
    //ponemos la musica
    Music gameplayMusic;
    gameplayMusic.openFromFile("music/Theme_for_Harold.ogg");
    gameplayMusic.setLoop(true);
    gameplayMusic.setVolume(80);
    gameplayMusic.play();
    while(window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::Left && snake.dx != 20) {
                    snake.dx = -20;
                    snake.dy = 0;
                }
                if(event.key.code == Keyboard::Right && snake.dx != -20) {
                    snake.dx = 20;
                    snake.dy = 0;
                }
                if(event.key.code == Keyboard::Up && snake.dy != 20) {
                    snake.dx = 0;
                    snake.dy = -20;
                }
                if(event.key.code == Keyboard::Down && snake.dy != -20) {
                    snake.dx = 0;
                    snake.dy = 20;
                }
                if(event.key.code == Keyboard::Escape) {
                    gameplayMusic.stop();
                    return;
                }
            }
        }
        /*
        if(colisionTimer < 35 && colisionTimer != 0)
            colisionTimer++;
        if(colisionTimer == 35)
            colisionTimer = 0;
            */
        //movimiento de la serpiente
        if(movementTimer == 80) {
            snake.moveSnake();
            movementTimer = 0;
            }
        movementTimer++;

        //ver si la serpiente ha comido algo
        if(snake.colisionFood(red) && movementTimer == 1) {
            snake.growUp();
            xRandom = numbersX[rand()%50+1];
            yRandom = numbersY[rand()%30+1];
            red.setPosition(xRandom, yRandom);
        }

        //Revisar si la serpiente muere
        snake.killSnake();
        if(!snake.alive) {
            gameplayMusic.stop();
            return;
        }

        //dibujar cosas en el window
        window->clear();
        for(int i = 0; i < snake.squares.size(); i++) {
            window->draw(snake.squares[i]);
        }
        window->draw(red);
        window->display();
    }
}
