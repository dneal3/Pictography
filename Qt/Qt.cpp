#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("Pictography");

    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

    QLabel *label = new QLabel("Hello Qt!");

    QLineEdit *line = new QLineEdit;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button);
    layout->addWidget(label);
    layout->addWidget(line);
    window->setLayout(layout);

    window->show();

    return app.exec();
}
