#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "tictactoewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void startNewGame();
    void updateNameLabels();
    void handleGameOver(Player winner);
private:
    Ui::MainWindow *ui;
    void setLabelBold(QLabel *label, bool isBold);
    int getWeight(QString const &input);
};

#endif // MAINWINDOW_H
