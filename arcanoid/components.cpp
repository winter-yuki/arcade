#include "components.hpp"

#include "controllers.hpp"
#include "engy/entity.hpp"
#include "engy/components/move.hpp"
#include "engy/controllers/controller.hpp"
#include "engy/defs.hpp"
#include "gamewidget.hpp"
#include "entities.hpp"


using namespace std::placeholders;


HP::HP(int hp)
    : INITIAL_HP_(hp)
    , hp_(hp)
{
    connect(this, &Component::entitySetted, this, &HP::entityAdded);
}


void HP::changeHp(int dHp)
{
    assert(textItem_);
    hp_ += dHp;
    textItem_->setPlainText(QString("%1/%2").arg(hp_).arg(INITIAL_HP_));
    if (hp_ <= 0) {
        entity()->deleteLater();
    }
}


void HP::entityAdded()
{
    assert(entity());
    connect(entity(), &Engy::Entity::formChanged, this, &HP::formChanged);
    if (entity()->form()) {
        formChanged();
    }
}


void HP::formChanged()
{
    assert(entity());
    assert(entity()->form());
    textItem_ = new QGraphicsTextItem(entity()->form());
    textItem_->setTextWidth(entity()->form()->boundingRect().width());
    changeHp(0);
}


PlatformSize::PlatformSize(qreal c, int hits)
    : coef_(c)
    , hitsLeft_(hits)
{
    assert(c > 0);
    assert(hits > 0);

    connect(this, &Engy::Component::entitySetted, [this] {
        assert(entity()->name() == Player::NAME);

        auto size = entity()->form()->boundingRect().size();
        auto form = Player::createForm(entity()->form()->pos(),
        { size.width() * coef_, size.height() });

        entity()->addForm(form);
    });
}


PlatformSize::~PlatformSize()
{
    if (!entity()) {
        return;
    }

    auto size = entity()->form()->boundingRect().size();
    auto form = Player::createForm(entity()->form()->pos(),
    {size.width() / coef_, size.height()});
    entity()->addForm(form);
}


void PlatformSize::counter(Engy::Entity * a, Engy::Entity * b)
{
    assert(a->name() == Ball::NAME);
    if (b->name() == Player::NAME) {
        if (auto c = b->findComponent<PlatformSize>()) {
            assert(c->hitsLeft_ > 0);
            --c->hitsLeft_;
            if (c->hitsLeft_ == 0) {
                c->deleteLater();
            }
        }
    }
}


Shimmer::Shimmer(int period)
{
    connect(this, &Engy::Component::entitySetted, [this, period] {
        startTimer(period);
    });
}


Shimmer::~Shimmer()
{
    if (item_) {
        delete item_;
    }
}


void Shimmer::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event)
    assert(entity());

    if (item_) {
        assert(!entity()->form());
        entity()->addForm(item_);
        item_ = nullptr;
    } else {
        item_ = entity()->extractForm();
    }
}


VMod::VMod(float amplitude, int lifeTime)
    : amplitude_(amplitude)
    , lifeTime_ (lifeTime)
{
    connect(this, &Component::entitySetted, this, &VMod::entitySetted);
}


VMod::~VMod()
{
    qDebug() << "VMod deleted";

    if (!entity()) {
        return;
    }

    if (auto move = entity()->findComponent<Engy::Move>()) {
        move->setBlock(false);
        disconnect(move, &Engy::Move::vChanged, this, &VMod::vUpdated);
    }
}


void VMod::entitySetted()
{
    auto move = entity()->findComponent<Engy::Move>();
    if (!move) {
        qDebug() << "Speed modifier assigned to entity with no move component";
        return;
    }

    // Until self deletion.
    startTimer(lifeTime_);

    move->setBlock(true);
    v0_ = move->v();
    v_ = v0_;

    timer_ = new Engy::Timer(this);
    timer_->start(UPDATE_INTERVAL);

    connect(timer_, &Engy::Timer::tickTime, this, &VMod::updateSpeed);
    connect(timer_, &Engy::Timer::tickdt,   this, &VMod::updatePos);
    connect(move,   &Engy::Move::vChanged,  this, &VMod::vUpdated);
}


void VMod::updateSpeed(int64_t time)
{
    float c = 0.5f + amplitude_ + amplitude_ * float(std::sin(time / 200));
    v_ = v0_ * c;
}


void VMod::updatePos(int64_t dt)
{
    assert(entity());
    entity()->form()->moveBy(qreal(v_.x()) * dt, qreal(v_.y()) * dt);
}


void VMod::vUpdated(QVector2D newV)
{
    v0_ = newV.normalized() * v0_.length();
    updateSpeed(timer_->time());
    updatePos(timer_->interval());
}


void VMod::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event)
    deleteLater();
}


Engy::Collisions::Handler BallWaiter::handler()
{
    return std::bind(&BallWaiter::hdl, this, _1, _2);
}


void BallWaiter::hdl(Engy::Entity * a, Engy::Entity * b)
{
    assert(a->name() == Player::NAME);

    if (b->name() == Ball::NAME) {
        auto bk = Engy::Component::create<BallKeeper>(a);
        b->addComponent(bk);

        auto space = Engy::Controller::create<SpaceButton>(a, [bk] {
            bk->deleteLater();
        });
        connect(bk, &BallKeeper::destroyed, [space] {
            space->deleteLater();
        });

        // TODO
        // a->removeComponent<Engy::Collisions>();
        deleteLater();
    }
}


BallKeeper::BallKeeper(Engy::Entity * player)
    : player_([player] {
    assert(player);
    assert(player->name() == Player::NAME);
    return player; } ())
    , prevPos([player] {
    assert(player->form());
    return player->form()->pos();} ())
{
    connect(this, &Engy::Component::entitySetted, [this] {
        assert(entity()->name() == Ball::NAME);

        // To have movement control
        entity()->removeComponent<VMod>();
        entity()->addComponent(Engy::Component::create<Engy::DisReflector>());
        if (auto move = entity()->findComponent<Engy::Move>()) {
            move->setBlock(true);
        }

        startTimer(UPDATE_INTERVAL);
    });
}


BallKeeper::~BallKeeper()
{
    if (entity()) {
        entity()->removeComponent<Engy::DisReflector>();
        if (auto move = entity()->findComponent<Engy::Move>()) {
            move->setBlock(false);
        }
    }
}


void BallKeeper::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event)
    assert(entity());
    assert(player_);
    assert(player_->form());

    auto dpos = player_->form()->pos() - prevPos;
    prevPos = player_->form()->pos();
    entity()->form()->moveBy(dpos.x(), dpos.y());
}






















