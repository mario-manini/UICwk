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

    // Create descriptions of all buttons.
    QLabel* PO_Label = new QLabel("Show statistics of the 25 most common pollutants");
    QLabel* POP_Label = new QLabel("Show statistics for Persistent Organic Pollutants");
    QLabel* FC_Label = new QLabel("Show statistics Flourinated compunds Pollutants");
    QLabel* CD_Label = new QLabel("See if levels are safe");

    // Center labels
    PO_Label->setAlignment(Qt::AlignCenter);
    POP_Label->setAlignment(Qt::AlignCenter);
    FC_Label->setAlignment(Qt::AlignCenter);
    CD_Label->setAlignment(Qt::AlignCenter);

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
    layout->addWidget(PO_Label);
    layout->addWidget(POP_Button);
    layout->addWidget(POP_Label);
    layout->addWidget(FC_Button);
    layout->addWidget(FC_Label);
    layout->addWidget(CD_Button);
    layout->addWidget(CD_Label);

    //Create window
    QWidget window;
    window.setLayout(layout);
    window.setMinimumSize(930, 400);
    window.setWindowTitle("Choose a category to take a closer look");
    window.show();

    return app.exec();
}
