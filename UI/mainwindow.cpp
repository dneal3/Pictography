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
    ui->EncryptionMenu->findChild<QPushButton *>("viewButton")->setEnabled(false);
    ui->EncryptionMenu->hide();
    ui->DecryptionMenu->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideMainMenu()
{
    ui->MainMenuWidget->hide();
}
void MainWindow::showMainMenu()
{
    ui->MainMenuWidget->show();
}

void MainWindow::hideEncryptMenu()
{
    ui->EncryptionMenu->hide();
}
void MainWindow::showEncryptMenu()
{
    ui->EncryptionMenu->show();

}
void MainWindow::hideDecryptMenu()
{
    ui->DecryptionMenu->hide();
}
void MainWindow::showDecryptMenu()
{
    ui->DecryptionMenu->show();
}
void MainWindow::on_pushButton_clicked()
{
    this->hideMainMenu();
    this->showEncryptMenu();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hideMainMenu();
    this->showDecryptMenu();
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
    ui->EncryptionMenu->findChild<QPushButton *>("viewButton")->setEnabled(true);
    ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("Encryption complete, view your encrypted image!");
}

void MainWindow::on_BackButton_clicked()
{
    this->hideEncryptMenu();
    this->showMainMenu();
}


void MainWindow::on_BackButton_2_clicked()
{
    this->hideDecryptMenu();
    this->showMainMenu();
}

void MainWindow::on_StartDecryption_clicked()
{
    QPlainTextEdit *temp = ui->DecryptionMenu->findChild<QPlainTextEdit *>("InStringTextEdit_Decrypt");
    if(temp == nullptr || temp->toPlainText().isNull())
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("An unexpected error occured! Restart program");\
        return ;
    }
    QString tempStr = temp->toPlainText();
    if(tempStr.isEmpty())
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("Input text before running");
        return ;
    }
    ValidData valididater(tempStr.toStdString());
    if(!valididater.ValidateData())
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("Input text was invalid");
        return ;
    }
    //TODO show decrypted string to person
    temp->clear();
    ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("Encryption complete!");
}
