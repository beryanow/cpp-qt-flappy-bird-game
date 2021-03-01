#include "GameWindow.h"
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

// конструирует класс игрового окна
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    gameWindowWidth = 380;
    gameWindowsHeight = 490;

    this->setFixedSize(gameWindowWidth, gameWindowsHeight);
    this->setWindowTitle("Flappy Bird");

    for (auto &pipe : pipes) {
        pipe = new Pipe(this);
    }

    for (auto &floor : floors) {
        floor = new Floor(this);
    }

    for (int i = 0; i < digitCount; i++) {
        digitHundreds[i] = new Digit(this);
        digitHundreds[i]->setSource(QString::fromStdString(":Image/" + std::to_string(i) + ".png"));
        digitHundreds[i]->setVisible(false);

        digitDozens[i] = new Digit(this);
        digitDozens[i]->setSource(QString::fromStdString(":Image/" + std::to_string(i) + ".png"));
        digitDozens[i]->setVisible(false);

        digitOnes[i] = new Digit(this);
        digitOnes[i]->setSource(QString::fromStdString(":Image/" + std::to_string(i) + ".png"));
        digitOnes[i]->setVisible(false);
    }

    bird = new Bird(this);

    createGame();
}

// рисует фоновое изображение
void GameWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap backgroundPixmap;

    backgroundPixmap.load(":/Image/bg.png");
    painter.drawPixmap(0, 0, 380, 450, backgroundPixmap);
}

// обрабатывает щелчки левой кнопкой мыши
void GameWindow::mousePressEvent(QMouseEvent *event) {
    if (gameState == NEW) {
        if (event->button() == Qt::LeftButton) {
            startGame();
        }
    } else if (gameState == CURRENT) {
        if (event->button() == Qt::LeftButton) {
            updateBirdJump();
        }
    } else if (gameState == FINISHED) {
        if (event->button() == Qt::LeftButton) {
            createGame();
        }
    }
}

// обрабатывает нажатия пробела
void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (gameState == NEW) {
        if (event->key() == Qt::Key_Space) {
            startGame();
        }
    } else if (gameState == CURRENT) {
        if (event->key() == Qt::Key_Space) {
            updateBirdJump();
        }
    } else if (gameState == FINISHED) {
        if (event->key() == Qt::Key_Space) {
            createGame();
        }
    }
}

// отвечает за инициализацию частей пола
void GameWindow::initializeFloor() {
    for (int i = 0; i < floorCount; i++) {
        floors[i]->move(0 + i * floors[0]->getGap(), 450);
    }

    floorTimer = new QTimer(this);
    connect(floorTimer, SIGNAL(timeout()), this, SLOT(floorShift()));
}

// отвечает за инициализацию цифр
void GameWindow::initializeDigits() {
    for (int i = 0; i < digitCount; i++) {
        digitHundreds[i]->move(gameWindowWidth / 2 - 35 - 20, 20);
    }

    for (int i = 0; i < digitCount; i++) {
        digitDozens[i]->move(gameWindowWidth / 2 - 20, 20);
    }

    for (int i = 0; i < digitCount; i++) {
        digitOnes[i]->move(gameWindowWidth / 2 + 35 - 20, 20);
    }
}

// отвечает за инициализацию труб
void GameWindow::initializePipes() {
    // определяет начальную позицию вне видимого пространства
    int pipeStartPosition = gameWindowWidth + 10;

    for (int i = 0; i < pipeCount; i++) {
        // инициализирует случайное смещение трубы сверху
        int pipeVerticalShift = QRandomGenerator::global()->generate() % pipes[0]->getGap();

        pipes[i]->move(pipeStartPosition + i * pipes[0]->getGap(), -pipes[0]->getGap() + pipeVerticalShift);
    }

    pipeTimer = new QTimer(this);
    connect(pipeTimer, SIGNAL(timeout()), this, SLOT(pipeShift()));
    connect(pipeTimer, SIGNAL(timeout()), this, SLOT(pipeBirdCollision()));
}

void GameWindow::initializeBird() {
    // изначальная позиция птицы
    bird->move(60, 250);

    this->birdShiftValues[0] = -3;
    this->birdShiftValues[1] = -4;
    this->birdShiftValues[2] = -3;
    this->birdShiftValues[3] = -2;
    this->birdShiftValues[4] = -1;
    this->birdShiftValues[5] = -1;
    this->birdShiftValues[6] = -1;
    this->birdShiftValues[7] = 0;
    this->birdShiftValues[8] = 1;
    this->birdShiftValues[9] = 1;
    this->birdShiftValues[10] = 2;
    this->birdShiftValues[11] = 2;
    this->birdShiftValues[12] = 2;
    this->birdShiftValues[13] = 3;
    this->birdShiftValues[14] = 4;

    this->birdShiftValueIndex = 0;

    birdShiftValue = 0;

    birdTimer = new QTimer(this);
    connect(birdTimer, SIGNAL(timeout()), this, SLOT(birdShift()));
}

void GameWindow::updateBirdJump() {
    birdShiftValueIndex = 0.0;
    // возвращает изначальное состояние смещений для прыжка
    birdShiftValue = birdShiftValues[int(birdShiftValueIndex)];
}

void GameWindow::updateDigitLabel(int successEnterAmount) {
    int ones = successEnterAmount % 10;
    successEnterAmount /= 10;
    int dozens = successEnterAmount % 10;
    successEnterAmount /= 10;
    int hundreds = successEnterAmount % 10;

    for (int i = 0; i < digitCount; i++) {
        digitOnes[i]->setVisible(false);
        digitDozens[i]->setVisible(false);
        digitHundreds[i]->setVisible(false);
    }

    digitOnes[ones]->setVisible(true);
    digitDozens[dozens]->setVisible(true);
    digitHundreds[hundreds]->setVisible(true);
}

// обрабатывает смещение птицы
void GameWindow::birdShift() {
    for (int i = 0; i < pipeCount; i++) {
        if (pipes[i]->pos().x() == bird->pos().x()) {
            successEnterAmount++;
        }
    }

    updateDigitLabel(successEnterAmount);

    bird->move(bird->pos().x(), bird->pos().y() + birdShiftValue);

    // отвечает за плавный прыжок птицы
    if (birdShiftValueIndex < 14.0)
        birdShiftValueIndex += 0.2;
    else {
        birdShiftValueIndex = 14.0;
    }

    birdShiftValue = birdShiftValues[int(birdShiftValueIndex)];

    // отвечает за обработку ситуации, когда птица достигла пола (происходит завершение игры)
    if (bird->pos().y() + bird->height() >= 450 + 10) {
        bird->move(bird->pos().x(), 450 - bird->height() + 10);

        birdTimer->stop();
        stopGame();
    }
}

// обрабатывает смещение труб
void GameWindow::pipeShift() {
    for (int i = 0; i < pipeCount; i++) {
        pipes[i]->move(pipes[i]->pos().x() - 1, pipes[i]->pos().y());
    }
}

// обрабатывает смещение пола
void GameWindow::floorShift() {
    for (int i = 0; i < floorCount; i++) {
        floors[i]->move(floors[i]->pos().x() - 1, 450);
    }
}

// отвечает за обработку ситуации, когда птица достигла трубы (происходит завершение игры)
void GameWindow::pipeBirdCollision() {
    int birdRx = bird->pos().x() + 30;
    int birdDy = bird->pos().y() + 30;

    for (int i = 0; i < pipeCount; i++) {
        if (birdRx >= pipes[i]->pos().x() && bird->pos().x() <= pipes[i]->pos().x() + pipes[i]->width() - 10) {
            if (bird->pos().y() <= (pipes[i]->pos().y() + 300) || birdDy >= (pipes[i]->pos().y() + 300 + pipes[i]->getGap())) {
                birdTimer->stop();
                stopGame();
            }
        }
    }
}

// отвечает за создание игры
void GameWindow::createGame() {
    gameState = NEW;

    initializeBird();
    initializePipes();
    initializeFloor();
    initializeDigits();

    updateDigitLabel(successEnterAmount);
}

// отвечает за остановку игры
void GameWindow::stopGame() {
    gameState = FINISHED;

    // останавливает таймеры
    pipeTimer->stop();
    floorTimer->stop();

    successEnterAmount = 0;
}

// отвечает за начало игры
void GameWindow::startGame() {
    gameState = CURRENT;

    // запускает все таймеры
    birdTimer->start(birdActionPeriod);
    pipeTimer->start(pipeActionPeriod);
    floorTimer->start(floorActionPeriod);
}
