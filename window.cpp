#include "game.h"
#include "window.h"
#include <QDesktopWidget>
#include <QtWidgets>
#include <QApplication>

Window::Window() : QMainWindow(0) {

    game = new Game(this);
    setCentralWidget(game);
    game->setFocus();
    QAction *NewAction = new QAction(tr("&New Game"), this);
    QAction *ShowAction = new QAction(tr("&Show Shortest Path"), this);
    QAction *abtAction = new QAction(tr("About PathFinder"), this);
    connect(NewAction, SIGNAL(triggered()), SLOT(startNewGame()));
    connect(ShowAction, SIGNAL(triggered()), SLOT(showShortestPath()));
    connect(abtAction, SIGNAL(triggered()), SLOT(showAbout()));

    QMenu *menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(NewAction);
    menu->addAction(ShowAction);
    menu->addSeparator();
    menu->addAction(abtAction);
    setWindowTitle(tr("PathFinder"));

}

void Window::startNewGame() {
    game->resetGame();
}

void Window::showShortestPath() {
    game->showSolution();
    QMessageBox msgBox;
    msgBox.setText("You cheated! The only way to continue playing is to start a new game.");
    msgBox.exec();
}

void Window::showAbout() {
    QMessageBox msgBox;
    msgBox.setText("Pathfinders is a simple game where you must take the shortest path to get to the goal point (the orange box). Use the arrow keys to navigate.\nBe careful though, you must take a minimum number of steps to get there or you fail.\n\nCoded by Adel Johar");
    msgBox.exec();
}
