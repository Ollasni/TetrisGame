#ifndef FIGURES_H
#define FIGURES_H

#include <QWidget>
#include <QBasicTimer>
class TypesFigure
{
public:
    void randomShape();
    int newShape;
    int coords[4][3];
    int numbOfFigure[6] =  { 0, 1, 2, 3, 4, 5 };
    int coordsOfFigure[6][4][2] = {
                    { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
                    { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
                    { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
                    { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
                    { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
                    { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
    };

};


class Figures : public QWidget
{
    Q_OBJECT

    bool DeleteLine;
    bool started;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
public:
    int board[10][20];
    Figures(QWidget *parent = nullptr);
    ~Figures();
    TypesFigure figure;
    void gameOver(QPainter &qp);
    void cleanBoard();
    int X;
    int Y;
    void pixDown();
    void newPiece();
    bool checkForMove(const TypesFigure &newPiece, int newX, int newY);

    QBasicTimer timer;
};
#endif // FIGURES_H
