#pragma once

#include "stdafx.hpp"


class Border final
        : public QGraphicsRectItem {
public:
    Border(QRectF rect, QGraphicsRectItem * parent = nullptr)
        : QGraphicsRectItem(rect, parent) {}
};
