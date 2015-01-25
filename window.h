#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class Game;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

private slots:
    void startNewGame();
    void showShortestPath();
    void showAbout();

private:
    Game *game;

};

#endif
