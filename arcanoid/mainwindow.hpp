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
    void createGame();

private:
    Engy::Game * game_ = nullptr;
    int score_ = 0;
};
