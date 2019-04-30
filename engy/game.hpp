#pragma once

#include "stdafx.hpp"
#include "entity.hpp"
#include "timer.hpp"
#include "controllers/field.hpp"


namespace Engy {

class Game final
        : private QGraphicsView {
public:
    explicit Game(QWidget * parent = nullptr);
    ~Game();

    void launch();

    void setFrameRate(int64_t fr);
    int64_t frameRate() const;
    void setSceneSize(QSize size);
    QSize sceneSize() const;
    void setBg(QBrush b);

    QGraphicsScene * scene();

    void addToField(EntityW entity);
    template <class FIt> void addToField(FIt begin, FIt end);

    // To admit entity adding to entity list on construction
    friend EntityS Entity::create(Game * game);

private:
    void addEntity(EntityS entity);

private:
    int64_t frameRate_ = 60;
    QSize sceneSize_ = { 720, 720 };

    QGraphicsScene * scene_;
    Timer * timer_;
    FieldP  field_;
    std::vector<EntityS> entities_;
};


template <class FIt>
void Game::addToField(FIt begin, FIt end) {
    std::copy(begin, end, std::back_inserter(field_->entities()));
}

} // Engy
