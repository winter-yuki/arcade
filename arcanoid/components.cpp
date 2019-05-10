#include "components.hpp"

#include "engy/entity.hpp"
#include "engy/components/move.hpp"
#include "gamewidget.hpp"
#include "entities.hpp"


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
        {size.width() * coef_, size.height()});

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
    timer_->start(15); /*60fps*/

    connect(timer_, &Engy::Timer::tickTime, this, &VMod::updateSpeed);
    connect(timer_, &Engy::Timer::tickdt, this, &VMod::updatePos);
    connect(move, &Engy::Move::vChanged, this, &VMod::vUpdated);
    connect(this, &VMod::entityDeleted, [this] {
        deleteLater();
    });
}


void VMod::updateSpeed(int64_t time)
{
    if (auto move = entity()->findComponent<Engy::Move>()) {
        float add = amplitude_ * float(std::sin(time / 100));
        v_ = { v0_.x() + add, v0_.y() + add };
    }
}


void VMod::updatePos(int64_t dt)
{
    assert(entity());
    entity()->form()->moveBy(qreal(v_.x()) * dt, qreal(v_.y()) * dt);
}


void VMod::vUpdated(QVector2D newV)
{
    // TODO wrong newV
    v0_ = newV.normalized() * v0_.length();
}


void VMod::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event)
    delete this;
}













