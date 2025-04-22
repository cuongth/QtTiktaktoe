#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QString player1Name READ player1Name WRITE setPlayer1Name)
    Q_PROPERTY(QString player2Name READ player2Name WRITE setPlayer2Name)
public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

private:
    Ui::ConfigurationDialog *ui;
public slots:
    void updateOKButtonState();
    void setPlayer1Name(QString &p1name);
    void setPlayer2Name(QString &p2name);
    QString player1Name() const;
    QString player2Name() const;
};

#endif // CONFIGURATIONDIALOG_H
