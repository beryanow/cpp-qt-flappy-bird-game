#ifndef PIPE_H
#define PIPE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class Pipe : public QWidget {
Q_OBJECT
public:
    explicit Pipe(QWidget *parent = 0);
    ~Pipe();
    int getGap();

private:
    int gap;

protected:
    void paintEvent(QPaintEvent *);
};

#endif
