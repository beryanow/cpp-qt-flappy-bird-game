#include "Floor.h"

Floor::Floor(QWidget *parent) : QWidget(parent) {
    gap = 405;
    this->setFixedSize(405, 40);
}

Floor::~Floor() = default;

void Floor::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap floorPixmap;

    floorPixmap.load(":Image/floor.png");
    painter.drawPixmap(0, 0, 405, 40, floorPixmap);
}

int Floor::getGap() {
    return gap;
}
