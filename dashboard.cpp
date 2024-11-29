#include "dashboard.hpp"
#include "pop.hpp"
#include "eli.hpp"

Dashboard::Dashboard(QWidget* parent)
    : QWidget(parent)
{
 
    QPushButton* PO_Button = new QPushButton("Pollutant Overview");
    QPushButton* POP_Button = new QPushButton("Persistent Organic Pollutants");
    QPushButton* ELI_Button = new QPushButton("Environmental Litter Indicators Page");
    QPushButton* FC_Button = new QPushButton("Fluorinated Compounds");
    QPushButton* CD_Button = new QPushButton("Compliance Dashboards");

 
    QLabel* PO_Label = new QLabel("Show statistics of the 25 most common pollutants:");
    QLabel* POP_Label = new QLabel("Show statistics for Persistent Organic Pollutants:");
    QLabel* ELI_Label = new QLabel("Summarise Physical Pollutants such as plastic litter: ");
    QLabel* FC_Label = new QLabel("Show statistics for Fluorinated compounds Pollutants:");
    QLabel* CD_Label = new QLabel("See if levels are safe:");

    //Link the buttons to actions (in the future)
    //QObject::connect(PO_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));
    QObject::connect(POP_Button, SIGNAL(clicked()), this, SLOT(onPOPButtonClicked())); 
    QObject::connect(ELI_Button, SIGNAL(clicked()), this, SLOT(onELIButtonClicked()));   //QObject::connect(FC_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));
    //QObject::connect(CD_Button, SIGNAL(clicked()), &app, SLOT(openfunc()));

    PO_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    PO_Button->setFixedSize(900, 100);
    PO_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    POP_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    POP_Button->setFixedSize(900, 100);
    POP_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    ELI_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    ELI_Button->setFixedSize(900, 100);
    ELI_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    FC_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    FC_Button->setFixedSize(900, 100);
    FC_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    CD_Button->setFont(QFont("Helvetica", 32, QFont::Bold));
    CD_Button->setFixedSize(900, 100);
    CD_Button->setStyleSheet("background-color: #3C9EFF; color: white;");

    //QObject::connect(POP_Button, SIGNAL(clicked()), this, SLOT(onPopButtonClicked()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(PO_Label);
    layout->addWidget(PO_Button);
    layout->addWidget(POP_Label);
    layout->addWidget(POP_Button);    
    layout->addWidget(ELI_Label);
    layout->addWidget(ELI_Button); 
    layout->addWidget(FC_Label);
    layout->addWidget(FC_Button);
    layout->addWidget(CD_Label);
    layout->addWidget(CD_Button);

    setLayout(layout);
    setMinimumSize(1000, 550);
    setWindowTitle("Water Quality Program");
}

void Dashboard::onPOPButtonClicked()
{
    // Create and show the new window when the button is clicked
    POPWindow* newWindow = new POPWindow();
    newWindow->show();
}

void Dashboard::onELIButtonClicked()
{
    // Create and show the new window when the button is clicked
    ELIWindow* newWindow = new ELIWindow();
    newWindow->show();
}