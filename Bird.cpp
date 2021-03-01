#include "Bird.h"

Bird::Bird(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(35, 35);
}

Bird::~Bird() = default;

void Bird::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap birdPixmap;

    birdPixmap.load(":/Image/bird.png");
    painter.drawPixmap(0, 0, 35, 35, birdPixmap);
}
