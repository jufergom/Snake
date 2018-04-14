#include "Snake.h"
#define ANCHO 1000
#define ALTO 600

using namespace sf;

Snake::Snake() {
    t1.loadFromFile("images/green_square.png");
    dx = 0;
    dy = -20;
    alive = true;

    for(int i = 0; i < 5; i++) {
        Sprite s(t1);
        s.setPosition(ANCHO/2, ALTO/2 + (i*20));
        squares.push_back(s);
    }
}

void Snake::moveSnake() {
    /*
    esto es para que la serpiente no se salga de la pantalla
    la verdad que tampoco es que funcione bien pero por los momentos
    lo dejare asi
    */
    if(squares[0].getPosition().x < 0) {
        squares[0].setPosition(ANCHO ,squares[0].getPosition().y);
    }
    else if(squares[0].getPosition().x >= ANCHO) {
        squares[0].setPosition(0 ,squares[0].getPosition().y);
    }
    else if(squares[0].getPosition().y < 0) {
        squares[0].setPosition(squares[0].getPosition().x ,ALTO);
    }
    else if(squares[0].getPosition().y >= ALTO) {
        squares[0].setPosition(squares[0].getPosition().x ,0);
    }

    Vector2f oldPos;
    Vector2f currentPos;
    for(int i = 0; i < squares.size(); i++) {
        if(i == 0) {
            oldPos = squares[i].getPosition();
            squares[i].move(dx, dy);
        }
        else {
            currentPos = squares[i].getPosition();
            squares[i].setPosition(oldPos);
            oldPos = currentPos;
        }
    }
}

void Snake::growUp() {
    Sprite s(t1);
    s.setPosition(squares[squares.size()-1].getPosition().x, squares[squares.size()-1].getPosition().y);
    squares.push_back(s);
}

void Snake::killSnake() {
    for(int i = 2; i < squares.size(); i++) {
        if(squares[0].getGlobalBounds().contains(squares[i].getPosition().x, squares[i].getPosition().y))
            alive = false;
    }
}

bool Snake::colisionFood(Sprite red) {
    return red.getGlobalBounds().contains(squares[0].getPosition().x, squares[0].getPosition().y);
}
