#ifndef DIGIT_H
#define DIGIT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

class Digit : public QWidget {
Q_OBJECT
public:
    explicit Digit(QWidget *parent = 0);
    ~Digit();
    void setSource(QString sourceImagePath);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString sourceImagePath = ":Image/0.png";
};

#endif
