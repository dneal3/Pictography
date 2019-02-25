#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void hideMainMenu();
    void showMainMenu();
    void hideEncryptMenu();
    void showEncryptMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_StartEncryption_clicked();

    void on_BackButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
