#include "Digit.h"

Digit::Digit(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(35, 42);
}

Digit::~Digit() = default;

void Digit::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap digitPixmap;

    digitPixmap.load(sourceImagePath);
    painter.drawPixmap(0, 0, 35, 42, digitPixmap);
}

void Digit::setSource(QString sourceImagePath) {
    this->sourceImagePath = sourceImagePath;
}