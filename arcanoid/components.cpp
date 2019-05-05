#include "components.hpp"

#include "engy/entity.hpp"


HP::HP(int hp)
    : INITIAL_HP_(hp)
    , hp_(hp)
{
//   auto text = new QGraphicsTextItem(entity()->form());
//   text->setPlainText(QString("Wow"));
//   text->setTextWidth(entity()->form()->boundingRect().width());
}


void HP::changeHp(int dHp)
{
    hp_ += dHp;
    qDebug() << "Hp changed " << hp_;
}
