#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../aux/validData.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *temp = ui->EncryptionMenu->findChild<QLabel *>("OutKeyLabel");
    temp->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->EncryptionMenu->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideMainMenu()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
}
void MainWindow::showMainMenu()
{
    ui->pushButton->show();
    ui->pushButton_2->show();
}

void MainWindow::hideEncryptMenu()
{
    ui->EncryptionMenu->hide();
}
void MainWindow::showEncryptMenu()
{
    ui->EncryptionMenu->show();
}
void MainWindow::on_pushButton_clicked()
{
    this->hideMainMenu();
    this->showEncryptMenu();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hideMainMenu();
}

void MainWindow::on_StartEncryption_clicked()
{

    QPlainTextEdit *temp = ui->EncryptionMenu->findChild<QPlainTextEdit *>("InStringTextEdit");
    if(temp == nullptr || temp->toPlainText().isNull())
    {
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("An unexpected error occured! Restart program");\
        return ;
    }
    QString tempStr = temp->toPlainText();
    if(tempStr.isEmpty())
    {
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("Input text before running");
        return ;
    }
    ValidData valididater(tempStr.toStdString());
    if(!valididater.ValidateData())
    {
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("Input text was invalid");
        return ;
    }
    ui->EncryptionMenu->findChild<QLabel *>("PutOutKeyLabel")->setText(tempStr);
    temp->clear();
    ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("Encryption complete!");
}

void MainWindow::on_BackButton_clicked()
{
    this->hideEncryptMenu();
    this->showMainMenu();
}

