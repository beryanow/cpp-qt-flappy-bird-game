#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

class Floor : public QWidget {
Q_OBJECT
public:
    explicit Floor(QWidget *parent = 0);
    ~Floor();
    int getGap();

protected:
    void paintEvent(QPaintEvent *);

private:
    int gap;
};

#endif
