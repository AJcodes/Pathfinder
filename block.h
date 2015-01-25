#ifndef BLOCK_H
#define BLOCK_H

#include <QImage>
#include <QRect>

class Block
{

  public:
    Block(int, int, int);
    ~Block();

  public:
    void resetState();
    int getInput();
    void setPlayer();
    void removePlayer();
    QRect getRect();
    void setRect(QRect);
    void setInput(int);
    void showPath();
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    int x;
    int y;
    int input;

};

#endif
