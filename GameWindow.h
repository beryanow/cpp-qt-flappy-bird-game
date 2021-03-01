#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>

#include "Bird.h"
#include "Pipe.h"
#include "Floor.h"
#include "Digit.h"

class GameWindow : public QMainWindow {
Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void birdShift();
    void floorShift();
    void pipeShift();
    void pipeBirdCollision();

private:
    void updateBirdJump();
    void initializePipes();
    void initializeBird();
    void initializeFloor();

    void initializeDigits();
    void updateDigitLabel(int successEnterAmount);

    void stopGame();
    void startGame();
    void createGame();

    double birdShiftValueIndex;
    double birdShiftValues[15];
    double birdShiftValue;

    int gameState;

    enum {
        FINISHED = 0,
        CURRENT = 1,
        NEW = 2
    };

    enum {
        pipeCount = 1000,
        floorCount = 500,
        digitCount = 10
    };

    Bird *bird;
    Pipe *pipes[pipeCount];
    Floor *floors[floorCount];

    Digit *digitHundreds[digitCount];
    Digit *digitDozens[digitCount];
    Digit *digitOnes[digitCount];

    QTimer *birdTimer;
    QTimer *pipeTimer;
    QTimer *floorTimer;

    int birdActionPeriod = 8;
    int pipeActionPeriod = 8;
    int floorActionPeriod = 8;

    int gameWindowWidth;
    int gameWindowsHeight;

    int successEnterAmount = 0;
};

#endif
