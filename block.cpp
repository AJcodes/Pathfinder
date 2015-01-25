#include "block.h"
#include <iostream>

Block::Block(int input, int x, int y)
{
  this->input = input;
  if (this->input == 0)
      image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze1.png");
  else if (this->input == 1)
      image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze2.png");
  else if (this->input == 2)
      image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze3.png");
  else if (this->input == 3)
      image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze4.png");
  this->x = x;
  this->y = y;
  rect = image.rect();
  rect.translate(this->x, this->y);
}

Block::~Block() {

   std::cout << ("Maze Block deleted\n");
}

QRect Block::getRect()
{
  return rect;
}

void Block::setRect(QRect rct)
{
  rect = rct;
}

int Block::getInput()
{
  return input;
}

void Block::setInput(int input)
{
    this->input = input;
}

void Block::showPath()
{
    if (this->input == 9)
    {
        image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze5.png");
        rect = image.rect();
        rect.translate(this->x, this->y);
    }
}

QImage & Block::getImage()
{
  return image;
}

void Block::setPlayer()
{
    input = 2;
    image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze3.png");
    rect = image.rect();
    rect.translate(this->x, this->y);
}

void Block::removePlayer()
{
    input = 0;
    image.load("C:\\Users\\Adel\\QTProjects\\Pathfinder\\maze1.png");
    rect = image.rect();
    rect.translate(this->x, this->y);
}
