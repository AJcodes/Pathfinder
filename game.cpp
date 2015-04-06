#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QPainter>
#include <QApplication>
#include <QThread>

int test[Game::SIZEI][Game::SIZEJ] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
                                      {0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
                                      {0,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,1},
                                      {0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,0,0,0,0},
                                      {0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0},
                                      {0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,0,0,1,0},
                                      {2,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,3},
                                      {0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0},
                                      {0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0},
                                      {0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,0},
                                      {0,1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0},
                                      {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}};

Game::Game(QWidget *parent) : QWidget(parent) {

    gameOver = false;
    gameWon = false;
    currstep = 0;
    minstep = 0;
    for (int i=0; i<SIZEI; i++) {
        for (int j=0; j<SIZEJ; j++) {
            block[i][j] = new Block(test[i][j], j*30, i*30);
            if(test[i][j] == 2) {
                playerx = j;
                playery = i;
            }
            if(test[i][j] == 3) {
                goalx = j;
                goaly = i;
            }
        }
    }
    maze = new int*[SIZEI];
    for (int i = 0; i < SIZEI; ++i) {
        maze[i] = new int[SIZEJ];
    }

    for (int i=0; i<SIZEI; i++) {
        for (int j=0; j<SIZEJ; j++) {
            maze[i][j] = test[i][j];
            if (maze[i][j] == 2)
                maze[i][j] = 0;
            if (maze[i][j] == 3)
                maze[i][j] = 0;
        }
    }

    maze = FindPath(playery, playerx, goaly, goalx);

    for (int i=0; i<SIZEI; i++)
        for (int j=0; j<SIZEJ; j++)
            if (maze[i][j] == 9 && block[i][j]->getInput() == 0)
                block[i][j]->setInput(9);
}

Game::~Game() {
    for (int i=0; i<SIZEI; i++)
        for (int j=0; j<SIZEJ; j++)
            delete block[i][j];
}

int Game::GetNodeContents(int** maze, int NodeNo) {
    return maze[NodeNo/SIZEJ][NodeNo - NodeNo/SIZEJ*SIZEJ];
}

void Game::ChangeNodeContents(int** maze, int NodeNo, int NewValue) {
    maze[NodeNo/SIZEJ][NodeNo - NodeNo/SIZEJ*SIZEJ] = NewValue;
}

int** Game::FindPath(int startY, int startX, int endY, int endX) {
    int startNode = startY*SIZEJ + startX;
    int endNode = endY*SIZEJ + endX;
    return ( Search(startNode, endNode) ) ;
}

int** Game::Search(int startNode, int endNode) {
    int Rows = SIZEI;
    int Cols = SIZEJ;
    int Max = Rows*Cols;
    int Queue[Max];
    int Origin[Max];
    int Front = 0, Rear = 0;
    Status statR = Ready;
    Status statW = Waiting;
    Status statP = Processed;

    if (GetNodeContents(maze, startNode) != 0 || GetNodeContents(maze, endNode)!= 0 )
        return NULL;

    int** mazeStatus = new int*[SIZEI];
    for (int i = 0; i < SIZEI; ++i)
        mazeStatus[i] = new int[SIZEJ];

    for(int i = 0; i < Rows; i++)
        for(int j = 0; j < Cols; j++)
            mazeStatus[i][j] = (int)statR;

    Queue[Rear] = startNode;
    Origin[Rear] = -1;
    Rear++;
    int Current, Left, Right, Top, Down;
    while(Front != Rear) {
         if (Queue[Front] == endNode)
             break;

         Current = Queue[Front];
         Left = Current - 1;
         if (Left >= 0 && Left/Cols == Current/Cols)
             if (GetNodeContents(maze, Left) == 0 )
                 if (GetNodeContents(mazeStatus, Left) == (int)statR) {
                     Queue[Rear] = Left;
                     Origin[Rear] = Current;
                     ChangeNodeContents(mazeStatus, Left, (int)statW);
                     Rear++;
                 }

         Right = Current + 1;
         if (Right < Max && Right/Cols == Current/Cols)
             if (GetNodeContents(maze, Right) == 0)
                 if (GetNodeContents(mazeStatus, Right) == (int)statR) {
                     Queue[Rear] = Right;
                     Origin[Rear] = Current;
                     ChangeNodeContents(mazeStatus, Right, (int)statW);
                     Rear++;
                 }

         Top = Current - Cols;
         if (Top >= 0 )
             if (GetNodeContents(maze, Top) == 0)
                 if (GetNodeContents(mazeStatus, Top) == (int)statR) {
                     Queue[Rear] = Top;
                     Origin[Rear] = Current;
                     ChangeNodeContents(mazeStatus, Top, (int)statW);
                     Rear++;
                 }

         Down = Current + Cols;
         if (Down < Max )
             if (GetNodeContents(maze, Down) == 0)
                 if (GetNodeContents(mazeStatus, Down) == (int)statR) {
                     Queue[Rear] = Down;
                     Origin[Rear] = Current;
                     ChangeNodeContents(mazeStatus, Down, (int)statW);
                     Rear++;
                 }

         ChangeNodeContents(mazeStatus, Current, (int)statP);
         Front++;

    }


    int** mazeSolved = new int*[SIZEI];
    for (int i = 0; i < SIZEI; ++i)
       mazeSolved[i] = new int[SIZEJ];
    for(int i = 0 ; i < Rows; i++)
        for(int j=0; j < Cols; j++)
            mazeSolved[i][j] = maze[i][j];


    Current = endNode;
    ChangeNodeContents(mazeSolved, Current, path);
    for(int i = Front; i >= 0; i--) {
        if (Queue[i] == Current) {
            Current = Origin[i];
            if (Current == -1)
                return mazeSolved;
            ChangeNodeContents(mazeSolved, Current, path);
            minstep++;
        }
    }

    return NULL;
}

void Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (gameWon) {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.width("You have reached the Goal!");
        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textWidth/2, 0, "You have reached the Goal!");
    }
    else if (gameOver) {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.width("You took too many steps! Try Again");
        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textWidth/2, 0, "You took too many steps! Try Again");
    }
    else{
        for (int i=0; i<SIZEI; i++)
            for (int j=0; j<SIZEJ; j++)
            painter.drawImage(block[i][j]->getRect(), block[i][j]->getImage());
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    if(!gameCheated) {
        switch (event->key()) {
        case Qt::Key_Left:
                if (block[playery][playerx-1]->getInput() == 3)
                    winGame();
                else if (block[playery][playerx-1]->getInput() != 1 && playerx-1 >= 0) {
                    block[playery][playerx]->removePlayer();
                    playerx--;
                    block[playery][playerx]->setPlayer();
                    currstep++;
                    if (currstep > minstep)
                        stopGame();
                }
        break;
        case Qt::Key_Right:
                if (block[playery][playerx+1]->getInput() == 3)
                    winGame();
                else if (block[playery][playerx+1]->getInput() != 1 && playerx+1 < SIZEJ) {
                    block[playery][playerx]->removePlayer();
                    playerx++;
                    block[playery][playerx]->setPlayer();
                    currstep++;
                    if (currstep > minstep)
                        stopGame();
                }
        break;
        case Qt::Key_Up:
                if (block[playery-1][playerx]->getInput() == 3)
                    winGame();
                else if (block[playery-1][playerx]->getInput() != 1 && playery-1 >= 0) {
                    block[playery][playerx]->removePlayer();
                    playery--;
                    block[playery][playerx]->setPlayer();
                    currstep++;
                    if (currstep > minstep)
                        stopGame();
                }
        break;
        case Qt::Key_Down:
                if (block[playery+1][playerx]->getInput() == 3)
                    winGame();
                else if (block[playery+1][playerx]->getInput() != 1 && playery+1 < SIZEI) {
                    block[playery][playerx]->removePlayer();
                    playery++;
                    block[playery][playerx]->setPlayer();
                    currstep++;
                    if (currstep > minstep)
                        stopGame();
                }
        break;
        case Qt::Key_Escape:
              qApp->exit();

        break;
        default:
            QWidget::keyPressEvent(event);
        }
    }
    repaint();
}

void Game::showSolution() {
    for (int i=0; i<SIZEI; i++)
        for (int j=0; j<SIZEJ; j++)
            block[i][j]->showPath();
    gameCheated = true;
}

void Game::stopGame() {
    gameOver = true;
}

void Game::winGame() {
    gameWon = true;
}

void Game::resetGame() {
    gameOver = false;
    gameWon = false;
    gameCheated = false;
    currstep = 0;
    minstep = 0;
    for (int i=0; i<SIZEI; i++) {
        for (int j=0; j<SIZEJ; j++) {
            block[i][j] = new Block(test[i][j], j*30, i*30);
            if(test[i][j] == 2) {
                playerx = j;
                playery = i;
            }
            if(test[i][j] == 3) {
                goalx = j;
                goaly = i;
            }
        }
    }
    maze = new int*[SIZEI];
    for (int i = 0; i < SIZEI; ++i)
        maze[i] = new int[SIZEJ];


    for (int i=0; i<SIZEI; i++) {
        for (int j=0; j<SIZEJ; j++) {
            maze[i][j] = test[i][j];
            if (maze[i][j] == 2)
                maze[i][j] = 0;
            if (maze[i][j] == 3)
             maze[i][j] = 0;
        }
    }

    maze = FindPath(playery, playerx, goaly, goalx);

    for (int i=0; i<SIZEI; i++) {
        for (int j=0; j<SIZEJ; j++) {
            if (maze[i][j] == 9 && block[i][j]->getInput() == 0)
                block[i][j]->setInput(9);
        }
    }

}

