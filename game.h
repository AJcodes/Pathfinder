#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <stdlib.h>
#include "block.h"

class Game : public QWidget
{
  Q_OBJECT

  public:
    Game(QWidget *parent = 0);
    ~Game();
    const static int SIZEI = 12;
    const static int SIZEJ = 23;
    const static int path = 9;
    void showSolution();
    void resetGame();

  protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    int** FindPath(int startY, int startX, int endY, int endX);
    int GetNodeContents(int** maze, int NodeNo);
    void ChangeNodeContents(int** maze, int NodeNo, int NewValue);
    int** Search(int startNode, int endNode);
    void stopGame();
    void winGame();

  private:
    enum Status { Ready, Waiting, Processed };
    int playerx;
    int playery;
    int goalx;
    int goaly;
    Block * block[SIZEI][SIZEJ];
    int** maze;
    int minstep;
    int currstep;
    bool gameOver;
    bool gameWon;
    bool gameCheated;


};

#endif
