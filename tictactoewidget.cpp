#include "tictactoewidget.h"
#include <QGridLayout>
#include <iostream>

void TicTacToeWidget::printPlayer(Player p)
{
    if (p == Player1)
        std::cout << "Player1 goes next" << std::endl;
    else if (p == Player2)
        std::cout << "Player2 goes next" << std::endl;
    else
        std::cout << "I don't know who goes next" << std::endl;
}

void TicTacToeWidget::closeGame(Player p)
{
    if (p == Player1)
        std::cout << "Player1 is a winner." << std::endl;
    else if (p == Player2)
        std::cout << "Player2 is a winner." << std::endl;
    else if (p == Draw)
        std::cout << "Draw game." << std::endl;
    else
        std::cout << "I don't know who wins." << std::endl;
    // It disconnects with slots printPlayer(Player) and closeGame(Player)
    // so slot handleButtonClick(int) is still be triggered on click.
    disconnect();
    // just one of 2 following statements can disconnect on slot handleButtonClick(int)
    mapper->disconnect(); // disconnect(mapper, nullptr, nullptr, nullptr);
    for (QPushButton *button: board)
        button->disconnect(); // disconnect(button, nullptr, nullptr, nullptr);
}

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
{
    m_currentPlayer = Player1;
    steps = 0;
    setupBoard();
    connect(this, SIGNAL(currentPlayerChanged(Player)), this, SLOT(printPlayer(Player)));
    connect(this, SIGNAL(gameOver(Player)), this, SLOT(closeGame(Player)));
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

void TicTacToeWidget::setCurrentPlayer(Player p)
{
    if (m_currentPlayer == p)
        return;
    m_currentPlayer = p;
    emit currentPlayerChanged(p);
}

void TicTacToeWidget::setupBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    mapper = new QSignalMapper(this);
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            button->setText(" ");
            gridLayout->addWidget(button, row, col);
            board.append(button);
            mapper->setMapping(button, board.count()-1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
    setLayout(gridLayout);
}

Player TicTacToeWidget::checkWinCondition(int id)
{
    QPushButton *button = board.at(id);
    QString const text = button->text();
    QPushButton * next_a;
    QPushButton * next_b;
    switch (id) {
    case 0:
        steps++;
        // 1st row 0-1-2
        next_a = board.at(1);
        next_b = board.at(2);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // diagonal 0-4-8
        next_a = board.at(4);
        next_b = board.at(8);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 1st column 0-3-6
        next_a = board.at(3);
        next_b = board.at(6);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 1:
        steps++;
        // 1st row 0-1-2
        next_a = board.at(0);
        next_b = board.at(2);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 2nd column 1-4-7
        next_a = board.at(4);
        next_b = board.at(7);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 2:
        steps++;
        // 1st row 0-1-2
        next_a = board.at(1);
        next_b = board.at(0);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // diagonal 2-4-6
        next_a = board.at(4);
        next_b = board.at(6);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 3rd column 2-5-8
        next_a = board.at(5);
        next_b = board.at(8);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 3:
        steps++;
        // 2nd row 3-4-5
        next_a = board.at(4);
        next_b = board.at(5);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 1st column 0-3-6
        next_a = board.at(0);
        next_b = board.at(6);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 4:
        steps++;
        // 2nd row 3-4-5
        next_a = board.at(3);
        next_b = board.at(5);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 2nd column 1-4-7
        next_a = board.at(1);
        next_b = board.at(7);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // diagonal 0-4-8
        next_a = board.at(4);
        next_b = board.at(8);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // diagonal 2-4-6
        next_a = board.at(4);
        next_b = board.at(6);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 5:
        steps++;
        // 2nd row 3-4-5
        next_a = board.at(4);
        next_b = board.at(3);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 3rd column 2-5-8
        next_a = board.at(2);
        next_b = board.at(8);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 6:
        steps++;
        // 1st column 0-3-6
        next_a = board.at(3);
        next_b = board.at(0);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // diagonal 2-4-6
        next_a = board.at(4);
        next_b = board.at(2);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 3rd row 6-7-8
        next_a = board.at(7);
        next_b = board.at(8);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 7:
        steps++;
        // column 2-4-7
        next_a = board.at(4);
        next_b = board.at(1);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 3rd row 6-7-8
        next_a = board.at(6);
        next_b = board.at(8);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    case 8:
        steps++;
        // 3rd column 2-5-8
        next_a = board.at(2);
        next_b = board.at(5);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // diagonal 0-4-8
        next_a = board.at(4);
        next_b = board.at(0);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        // 3rd row 6-7-8
        next_a = board.at(6);
        next_b = board.at(7);
        if (compare3(text, next_a->text(), next_b->text()))
            return m_currentPlayer;
        return Invalid;
    default:
        return Invalid;
    }
}

bool TicTacToeWidget::compare3(QString const &text, QString const a, QString const b)
{
    std::cout << "compare " << text.toStdString() << ", a = " << a.toStdString()
              << ", b = " << b.toStdString() << std::endl;
    if (text == a && text == b)
        return true;
    return false;
}

void TicTacToeWidget::handleButtonClick(int index)
{
    if (index < 0 || index >= board.size())
        return;
    QPushButton *button = board.at(index);
    std::cout << "handleButtonClick at " << index << std::endl;
    if (button->text() != " ")
        return;
    button->setText(m_currentPlayer == Player1 ? "X" : "O");
    Player winner = checkWinCondition(index);
    if (winner == Invalid)
    {
        setCurrentPlayer(m_currentPlayer == Player1 ? Player2 : Player1);
        if (steps == 9)
        {
            std::cout << "DRAW, steps == 9" << std::endl;
            emit gameOver(Draw);
        }
        else
        {
            std::cout << "Winner is still invalid, steps = " << steps << std::endl;
        }
    }
    else
    {
        std::cout << "gameOver" << std::endl;
        emit gameOver(winner);
    }
}
