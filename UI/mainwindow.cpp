#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../aux/validData.h"
#include<QProcess>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *temp = ui->EncryptionMenu->findChild<QLabel *>("OutKeyLabel");
    temp->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->EncryptionMenu->findChild<QPushButton *>("viewButton")->setEnabled(false);
    ui->DecryptionMenu->findChild<QPlainTextEdit *>("OutPTTextEdit_Decrypt")->setEnabled(false);
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
    filenameQS = ui->EncryptionMenu->findChild<QLineEdit *>("FileNameLineEdit")->text();
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
    if(filenameQS.isEmpty())
    {
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("Input filename before running");
        return ;
    }
    ValidData valididater(tempStr.toStdString());
    if(!valididater.ValidateData())
    {
        QString tempSize = QString::number(tempStr.size());
        QString errMsg = "Max character length: 999 Current length: "+tempSize;
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText(errMsg);
        return ;
    }
    QString fn_vtk = filenameQS+vtk;
    QProcess *encryptProcess = new QProcess;
    QStringList args;
    args << fn_vtk << filenameQS << tempStr;
    encryptProcess->setProgram("encrypt");
    encryptProcess->setArguments(args);
    encryptProcess->setEnvironment(QProcess::systemEnvironment());
    encryptProcess->start();

    encryptProcess->waitForStarted();
    encryptProcess->waitForFinished();
    encryptProcess->closeWriteChannel();
    encryptProcess->waitForReadyRead();
    QByteArray out= encryptProcess->readAllStandardOutput();
    QProcess::ProcessError err = encryptProcess->error();
    QString outErr= encryptProcess->readAllStandardError();
    if(err != 5)
    {
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog")->setText("An Error seems to have occured! Please re-encrypt");
        return ;
    }
    ui->EncryptionMenu->findChild<QLineEdit *>("PutOutKeyLineEdit")->setText(out);
    temp->clear();
    fn_png = filenameQS.toStdString() + ".png";
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
    QLineEdit *temp = ui->DecryptionMenu->findChild<QLineEdit *>("InStringTextEdit_Decrypt");
    QLineEdit *keyQTE = ui->DecryptionMenu->findChild<QLineEdit *>("InKeyLineEdit_Decrypt");
    if(keyQTE == nullptr)
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("KeyAn unexpected error occured! Restart program");
        return ;
    }
    QString key = keyQTE->text();

    if(temp == nullptr || temp->text().isNull())
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("An unexpected error occured! Restart program");\
        return ;
    }
    QString tempStr = temp->text();
    if(tempStr.isEmpty())
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("Input filename before running");
        return ;
    }
    if(key.isEmpty())
    {
        ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("Input key before running");
        return ;
    }

    QString fn_vtk = tempStr+vtk;
    QProcess *decryptProcess = new QProcess;
    QStringList args;
    args << fn_vtk << key;
    decryptProcess->setProgram("decrypt");
    decryptProcess->setArguments(args);
    decryptProcess->setEnvironment(QProcess::systemEnvironment());
    decryptProcess->start();

    decryptProcess->waitForStarted();
    decryptProcess->waitForFinished();
    decryptProcess->closeWriteChannel();
    decryptProcess->waitForReadyRead();
    QByteArray out= decryptProcess->readAllStandardOutput();
    QProcess::ProcessError err = decryptProcess->error();
    QString outErr= decryptProcess->readAllStandardError();
    if(err != 5)
    {
        ui->EncryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("An Error seems to have occured! Please re-decrypt");
        return ;
    }

    QPlainTextEdit *plainTextPlacement = ui->DecryptionMenu->findChild<QPlainTextEdit *>("OutPTTextEdit_Decrypt");
    plainTextPlacement->setEnabled(true);
    plainTextPlacement->setPlainText(out);


    temp->clear();
    keyQTE->clear();
    ui->DecryptionMenu->findChild<QLabel *>("ProgressLog_Decrypt")->setText("Decryption complete!");
}

void MainWindow::on_viewButton_clicked()
{
    std::string sysCall = "open " + fn_png;
    system(sysCall.c_str());
}
