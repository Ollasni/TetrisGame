#include "figures.h"
#include <QPainter>
#include <QKeyEvent>


Figures::Figures(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color:black;");
    resize(500, 1000);
    DeleteLine = false;
    started = true;
    cleanBoard();
    newPiece();
    timer.start(300, this);

}
void Figures::cleanBoard() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++)
            board[i][j] = 0;
    }
}

Figures::~Figures(){

}

void Figures::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(started){
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                int shape = board[j][20 - i - 1];

                if (shape != 0){
                        QPixmap pic("/home/olya/NewGame1/new1.jpg");
                        pic = pic.scaled(40, 40);
                        painter.drawImage( j * contentsRect().width() / 10, i * contentsRect().height() / 20, pic.toImage());
                }
            }
        }

        if (figure.newShape != 0) {
            for (int i = 0; i < 4; ++i) {
                int x = X + figure.coords[i][0];
                int y = Y - figure.coords[i][1];
                QPixmap pic("/home/olya/NewGame1/new.jpg");
                pic = pic.scaled(40,40);
                painter.drawImage(x * contentsRect().width() / 10 + 1,(20 - y - 1)* contentsRect().height() / 20 + 1,   pic.toImage());
            }
        }
    }
    else
        gameOver(painter);
}

void Figures::pixDown()
{
    if (!checkForMove(figure, X, Y - 1)){
        for (int i = 0; i < 4; ++i) {
            int x = X + figure.coords[i][0];
            int y = Y - figure.coords[i][1];
            // board[x][y] = figure.newShape;
        }

        if (!DeleteLine)
            newPiece();
    }
}



void Figures::newPiece()
{
    figure.randomShape();
    X = 5;
    Y = 10;
    if (!checkForMove(figure, X, Y)) {
        timer.stop();
        started = false;
    }
}

bool Figures::checkForMove(const TypesFigure &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.coords[i][0];
        int y = newY - newPiece.coords[i][1];
        if (x < 0 || x >= 10 || y < 0 || y >= 20)
            return false;
    }

    figure = newPiece;
    X = newX;
    Y = newY;
    update();
    return true;
}


void Figures::timerEvent(QTimerEvent *event)
{
        if (DeleteLine) {
            DeleteLine = false;
            newPiece();
        }
        else
            pixDown();
}


void Figures::keyPressEvent(QKeyEvent *event)
{
    int key = event -> key();
        if (key == Qt::Key_Left)
            checkForMove(figure, X - 1, Y);
        if (key == Qt::Key_Right)
            checkForMove(figure, X + 1, Y);
        if (key == Qt::Key_Down)
            pixDown();
}

void TypesFigure::randomShape()
{
    int figure = rand() % 5 + 1;
        for (int i = 0; i < 4 ; i++) {
            for (int j = 0; j < 2; j++)
                coords[i][j] = coordsOfFigure[figure][i][j];
        }
        newShape = figure;
}
void Figures::gameOver(QPainter &qp) {
        QString message = "Game over";
        QFont font("Courier", 15, QFont::DemiBold);

        qp.setPen(QColor(Qt::white));
        qp.setFont(font);
        qp.translate(QPoint(160, 400));
        qp.drawText(-5, 0, message);
    }
