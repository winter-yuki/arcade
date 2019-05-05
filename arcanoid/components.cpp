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


void HP::hpCounter(Engy::Entity * a, Engy::Entity * b)
{
    if (a->name() == "Ball" && b->name() == "Box") {
        if (auto hp = b->findComponent<HP>()) {
            hp->changeHp();
            if (hp->hp() <= 0) {
                b->deleteLater();
                return;
            }
        }
    }
}
