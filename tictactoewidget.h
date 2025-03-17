#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QPushButton>
#include <QWidget>
#include <QSignalMapper>

enum Player
{
    Invalid, Player1, Player2, Draw
};

class TicTacToeWidget : public QWidget
{
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = nullptr);
    ~TicTacToeWidget();
    void initNewGame();
    Player currentPlayer() const {return m_currentPlayer;}
    void setCurrentPlayer(Player p);
private:
    QList<QPushButton *> board;
    QSignalMapper *mapper;
    Player m_currentPlayer;
    void setupBoard();
    Player checkWinCondion(int id);
    bool compare3(QString const & text, QString const a, QString const b);
signals:
    void currentPlayerChanged(Player);
    void gameOver(Player);
public slots:
    void handleButtonClick(int);
    void closeGame(Player);
private slots:
    void printPlayer(Player);
};
#endif // TICTACTOEWIDGET_H
