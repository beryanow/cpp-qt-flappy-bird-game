#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

class Bird : public QWidget {
Q_OBJECT
public:
    explicit Bird(QWidget *parent = 0);
    ~Bird() override;

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif
