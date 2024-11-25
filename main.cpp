#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create buttons
    QPushButton* PO_Button = new QPushButton("Pollutant Overview");
    QPushButton* POP_Button = new QPushButton("Persistent Organic Pollutants");
    QPushButton* FC_Button = new QPushButton("Flourinated Compounds");
    QPushButton* CD_Button = new QPushButton("Compliance Dashboards");

    // Create size, font etc for every buttons
    PO_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    PO_Button->setFixedSize(900, 100);
    PO_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    POP_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    POP_Button->setFixedSize(900, 100);
    POP_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    FC_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    FC_Button->setFixedSize(900, 100);
    FC_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    CD_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    CD_Button->setFixedSize(900, 100);
    CD_Button->setStyleSheet("background-color: #3C9EFF; color: white;");


    //Link the buttons to actions (in the future)
    //QObject::connect(PO_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));
    //QObject::connect(POP_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));
    //QObject::connect(FC_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));
    //QObject::connect(CD_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));

    // Create a layout and add buttons to the layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(PO_Button);
    layout->addWidget(POP_Button);
    layout->addWidget(FC_Button);
    layout->addWidget(CD_Button);

    //Create window
    QWidget window;
    window.setLayout(layout);
    window.setMinimumSize(930, 400);
    window.setWindowTitle("Choose a category to take a closer look");
    window.show();

    return app.exec();
}
