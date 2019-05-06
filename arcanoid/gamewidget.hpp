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
    void updateLifes(int dl = -1);
    void updateTitle();
    void endGame();

private:
    void createGame();

    std::vector<Engy::Entity *> makeBorders(double width = 10);
    std::vector<Engy::Entity *> makeField();

    void scoreCounter(Engy::Entity * a, Engy::Entity * b);
    void hpCounter(Engy::Entity * a, Engy::Entity * b) const;
    void bonusCreator(Engy::Entity * a, Engy::Entity * b);
    Bonus::Applier getRandomBonus();

    void bonusPoints(Engy::Entity * e);
    void bonusLifes (Engy::Entity * e);
    void trampoline (Engy::Entity * e);

private:
    const QVector2D INITIAL_BALL_V_ = { 0.2f, -0.3f };
    const QPointF INITIAL_BALL_POS_ = { 800, 800 };

    Engy::Game * game_ = nullptr;
    int score_ = 0;
    int lifes_ = 5;

    Engy::Entity * ball_ = nullptr;
};
