#pragma once

#include "component.hpp"


class Render final
        : public Component
        , public QGraphicsItem {
public:
    using Painter = std::function<void (QPainter *)>;

    Render(QGraphicsScene * scene, QGraphicsItem * parent = nullptr);
    ~Render() override;

    void setPainter(Painter p);

    QRectF boundingRect() const override;
    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) override;

private:
    QGraphicsScene * scene_;
    Painter          painter_;
};
