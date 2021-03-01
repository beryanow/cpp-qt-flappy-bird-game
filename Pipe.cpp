#include "Pipe.h"

Pipe::Pipe(QWidget *parent) : QWidget(parent) {
    gap = 200;
    this->setFixedSize(70, gap + 600);
}

Pipe::~Pipe() = default;

void Pipe::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pipePixmap;

    pipePixmap.load(":/Image/pipe1.png");
    painter.drawPixmap(0, 0, 70, 300, pipePixmap);

    pipePixmap.load(":/Image/pipe2.png");
    painter.drawPixmap(0, 300 + gap, 70, 300, pipePixmap);
}

int Pipe::getGap() {
    return gap;
}

