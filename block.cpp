#include "block.h"
#include <iostream>

Block::Block(int input, int x, int y) {
    this->input = input;
    switch(this->input) {
    case 0:
        image.load(":/images/maze1.png");
    break;
    case 1:
        image.load(":/images/maze2.png");
    break;
    case 2:
        image.load(":/images/maze3.png");
    break;
    case 3:
        image.load(":/images/maze4.png");
    break;
    }
    this->x = x;
    this->y = y;
    rect = image.rect();
    rect.translate(this->x, this->y);
}

Block::~Block() {
    std::cout << ("Maze Block deleted\n");
}

QRect Block::getRect() {
    return rect;
}

void Block::setRect(QRect rct) {
    rect = rct;
}

int Block::getInput() {
    return input;
}

void Block::setInput(int input) {
    this->input = input;
}

void Block::showPath() {
    if (this->input == 9)     {
        image.load(":/images/maze5.png");
        rect = image.rect();
        rect.translate(this->x, this->y);
    }
}

QImage & Block::getImage() {
    return image;
}

void Block::setPlayer() {
    input = 2;
    image.load(":/images/maze3.png");
    rect = image.rect();
    rect.translate(this->x, this->y);
}

void Block::removePlayer() {
    input = 0;
    image.load(":/images/maze1.png");
    rect = image.rect();
    rect.translate(this->x, this->y);
}
