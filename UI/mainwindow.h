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
    void hideDecryptMenu();
    void showDecryptMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_StartEncryption_clicked();

    void on_BackButton_clicked();

    void on_BackButton_2_clicked();

    void on_StartDecryption_clicked();

    void on_viewButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filenameQS;
    const QString vtk = ".vtk";
    std::string fn_png;
};

#endif // MAINWINDOW_H
