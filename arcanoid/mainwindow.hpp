#pragma once

#include <QMainWindow>
#include <engy/game.hpp>


class MainWindow final
        : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = nullptr);

public slots:
    void restartGame();
    void updateScore(int delta);
    void endGame();

private:
    void scoreCounter(Engy::Entity * a, Engy::Entity * b);
    void createGame();

    std::vector<Engy::Entity *> makeBorders(double width = 10);
    std::vector<Engy::Entity *> makeField();

private:
    Engy::Game * game_ = nullptr;
    int score_ = 0;
};
