#include "configurationdialog.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    //regex.setPattern("([1-9][0-9]{0,2}) [ ]?(mg|g|kg)");
    //regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    updateOKButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::updateOKButtonState()
{
    bool pl1NameEmpty = ui->player1Name->text().isEmpty();
    QString const txt2 = ui->player2Name->text();
    bool pl2NameEmpty = txt2.isEmpty();
    //QRegularExpressionMatch match = regex.match(txt2);
    //bool isWeight = match.hasMatch();
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    //okButton->setDisabled(pl1NameEmpty || pl2NameEmpty || !isWeight);
    okButton->setDisabled(pl1NameEmpty || pl2NameEmpty);
}

void ConfigurationDialog::setPlayer1Name(QString &p1name)
{
    ui->player1Name->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(QString &p2name)
{
    ui->player2Name->setText(p2name);
}

QString ConfigurationDialog::player1Name() const
{
    return ui->player1Name->text();
}

QString ConfigurationDialog::player2Name() const
{
    return ui->player2Name->text();
}
