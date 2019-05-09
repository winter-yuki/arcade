/**
  * @file
  */

#include "game.hpp"

#include "entity.hpp"


namespace Engy
{

Game::Game(QWidget * parent)
    : QGraphicsView(parent)
    , timer_(new Timer(this))
    , scene_(new QGraphicsScene)
{
    setScene(scene_);
    setSceneSize(sceneSize_);
    qDebug() << "Engy::Game created";
}


Game::~Game()
{
    // QGraphicsView doesn't take ownership of scene.
    delete scene_;

    for (auto e : es_) {
        assert(e);
        deleteEntity(e);
    }
}


void Game::launch()
{
    // Set game update timer
    timer_->start(UPDATE_INTERVAL);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    show();
    qDebug() << "Engy::Game launched";
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


QGraphicsScene const * Game::scene() const
{
    return scene_;
}


Timer * Game::timer()
{
    return timer_;
}


Timer const * Game::timer() const
{
    return timer_;
}


bool Game::addEntity(Entity * entity)
{
    auto rez = es_.insert(entity);
    return rez.second;
}


bool Game::removeEntity(Entity * entity)
{
    auto search = es_.find(entity);
    if (search != es_.end()) {
        es_.erase(entity);
        deleteEntity(entity);
        return true;
    }
    return false;
}


bool Game::forgetEntity(Entity * entity)
{
    return es_.erase(entity);
}


void Game::deleteEntity(Engy::Entity * e) const
{
    e->delGame();
    delete e;
}

} // Engy








