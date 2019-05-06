#pragma once

#include <QMainWindow>
#include <engy/game.hpp>
#include "entities.hpp"


class GameWidget final
        : public QMainWindow {
    Q_OBJECT
public:
    explicit GameWidget(QWidget * parent = nullptr);

public slots:
    void restartGame();
    void updateScore(int delta);
    void endGame();

private:
    void createGame();

    std::vector<Engy::Entity *> makeBorders(double width = 10);
    std::vector<Engy::Entity *> makeField();

    void scoreCounter(Engy::Entity * a, Engy::Entity * b);
    void hpCounter(Engy::Entity * a, Engy::Entity * b) const;
    void bonusCreator(Engy::Entity * a, Engy::Entity * b);
    Bonus::Applier getRandomBonus();

    void bonusPoints(Engy::Entity * a, Engy::Entity * b);

private:
    Engy::Game * game_ = nullptr;
    int score_ = 0;
};
