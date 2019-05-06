#include "components.hpp"

#include "engy/entity.hpp"


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



























