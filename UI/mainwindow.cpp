#include "mainwindow.h"
#include <QLabel> 
#include <QHBoxLayout>
#include <QCoreApplication>
 
 MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
 {
    encrypt_button = new QPushButton("Encrypt", this);

    // set size and location of the button
    encrypt_button->setGeometry(QRect(QPoint(100, 50), QSize(200, 50)));
 
    // Connect button signal to appropriate slot
    connect(encrypt_button, SIGNAL (released()), this, SLOT (handleButton()));

    // Create the button, make "this" the parent
    decrypt_button = new QPushButton("Decrypt", this);

    // set size and location of the button
    decrypt_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
 
    // Connect button signal to appropriate slot
    connect(decrypt_button, SIGNAL (released()), this, SLOT (handleButton()));
}
 
 void MainWindow::handleButton()
 {
    encrypt_button->setVisible(false);

    decrypt_button->setVisible(false);

    QLabel *label = new QLabel(this);
    label->setText("Enter a string to encrypt");
    label->showMaximized();
}
