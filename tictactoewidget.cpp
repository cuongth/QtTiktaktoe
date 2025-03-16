#include "tictactoewidget.h"
#include <QGridLayout>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
{
    setupBoard();
}

// Whenever a QObject instance is destroyed, it also deletes all its children.
// Since both the layout object and the buttons are
// the children of the TicTacToeWidget instance, they will all be deleted
// when the main widget is destroyed.
TicTacToeWidget::~TicTacToeWidget() {}

void TicTacToeWidget::initNewGame()
{
    for (QPushButton *button: board)
        button->setText(" ");
}

void TicTacToeWidget::setupBoard()
{
    // Alternatively, we might have passed this as a parameter to the layout's constructor.
    // QGridLayout *gridLayout = new QGridLayout(this);
    // then we don't neet to setLayout.
    QGridLayout *gridLayout = new QGridLayout;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            int x = (row+1)*(col+1);
            QString labelT = QString::number(x);
            button->setText(labelT);
            gridLayout->addWidget(button, row, col);
            board.append(button);
        }
    }
    setLayout(gridLayout);
}
