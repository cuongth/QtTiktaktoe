#include <QMessageBox>
#include "configurationdialog.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->gameBoard, SIGNAL(currentPlayerChanged(Player)), this, SLOT(updateNameLabels()));
    connect(ui->gameBoard, SIGNAL(gameOver(Player)), this, SLOT(handleGameOver(Player)));
    ui->gameBoard->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame()
{
    ConfigurationDialog dlg(this);
    if (dlg.exec() == QDialog::Rejected) {
        return; // do nothing if dialog rejected
    }
    ui->player1->setText(dlg.player1Name());
    QString const txt2 = dlg.player2Name();
    ui->player2->setText(txt2);
    ui->gameBoard->initNewGame();
    ui->gameBoard->setEnabled(true);
}

void MainWindow::updateNameLabels()
{
    setLabelBold(ui->player1, ui->gameBoard->currentPlayer() == Player::Player1);
    setLabelBold(ui->player2, ui->gameBoard->currentPlayer() == Player::Player2);
}

void MainWindow::setLabelBold(QLabel *label, bool isBold)
{
    QFont f = label->font();
    f.setBold(isBold);
    label->setFont(f);
}

void MainWindow::handleGameOver(Player winner)
{
    ui->gameBoard->setEnabled(false);
    QString msg;
    if (winner == Player::Draw) {
        msg = "Game ended with a draw.";
    } else {
        msg = QString("%1 wins").arg(winner == Player::Player1
                                ? ui->player1->text() : ui->player2->text());
    }
    QMessageBox::information(this, tr("Info"), msg);
}
