#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
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
    QString filenameQS = ui->EncryptionMenu->findChild<QLineEdit *>("FileNameLineEdit")->text();
    this->filename = filenameQS.toStdString();
    std::string tempfn;
    tempfn = this->filename+".vtk";
    char * * args = (char **)malloc(sizeof(char*)*3);
    args[0] = (char*)std::string("../bin/encrypt").c_str();
    args[1] = (char*)tempfn.c_str();
    args[2] = (char*)filename.c_str();
    fork();
   // execvp("../bin/encrypt", args);
    system("~/Desktop/cis/433/encryptionProj/CIS433Project/runEncrypt.sh");
  //  system("pwd");
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
