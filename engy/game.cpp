/**
  * @file
  */

#include "game.hpp"

#include "entity.hpp"
#include "controllers/ecarrowkeys.hpp"
#include "controllers/eccollisions.hpp"
#include "controllers/collision_handlers.hpp"
#include "components/move.hpp"
#include "timer.hpp"


namespace Engy
{

Game::Game(QWidget * parent)
    : QGraphicsView(parent)
    , scene_(new QGraphicsScene)
    , timer_(new Timer(this))
    , field_(makeField()) // Create registry with tangible items
{
    setScene(scene_);
    setSceneSize(sceneSize_);
    qDebug() << "Engy::Game created";
}


Game::~Game()
{
    // QGraphicsView doesn't take ownership of scene.
    delete scene_;
}


void Game::launch()
{
    // Set game update timer
    timer_->start(int(1.0 / frameRate_ * 1000));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    show();
    qDebug() << "Engy::Game launched";
}


void Game::setFrameRate(int64_t fr)
{
    frameRate_ = fr;
}


int64_t Game::frameRate() const
{
    return frameRate_;
}


void Game::setSceneSize(QSize size)
{
    sceneSize_ = size;
    assert(scene_);
    scene_->setSceneRect({{0, 0}, sceneSize_});
    setFixedSize(sceneSize_ + QSize(5, 5)); // To see whole scene
    emit sceneResized();
}


QSize Game::sceneSize() const
{
    return sceneSize_;
}


void Game::setBg(QBrush b)
{
    setBackgroundBrush(b);
}


QGraphicsScene * Game::scene()
{
    return scene_;
}


Timer * Game::timer()
{
    return timer_;
}


FieldS Game::field()
{
    return field_;
}


void Game::addToField(EntityW entity)
{
    field_->addEntity(entity);
}


void Game::addEntity(EntityS entity)
{
    entities_.push_back(entity);
}


void Game::removeEntity(EntityS entity)
{
    assert("All references outside to entity should be deleted" &&
           entity.use_count() == 2);
    entities_.erase(remove(entities_.begin(),
                           entities_.end(), std::move(entity)), entities_.end());
}

} // Engy








