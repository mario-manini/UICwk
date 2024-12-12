#include "dashboard.hpp"
#include "pollutants_overview.hpp"
#include "pop.hpp"
#include "eli.hpp"
#include "fluorinated.hpp"
#include "physicalPage.hpp" 

Dashboard::Dashboard(QWidget* parent)
    : QWidget(parent)
{
    // Create buttons
    QPushButton* OV_Button = new QPushButton(tr("Pollutant Overview"));
    QPushButton* POP_Button = new QPushButton(tr("Persistent Organic Pollutants"));
    QPushButton* ELI_Button = new QPushButton(tr("Environmental Litter Indicators"));
    QPushButton* FC_Button = new QPushButton(tr("Fluorinated Compounds"));
    QPushButton* CD_Button = new QPushButton(tr("Compliance Dashboards"));

    // Create labels
    QLabel* OV_Label = new QLabel(tr("Show statistics of the most common pollutants:"));
    QLabel* POP_Label = new QLabel(tr("Show statistics for Persistent Organic Pollutants:"));
    QLabel* ELI_Label = new QLabel(tr("Summarise Physical Pollutants such as plastic litter:"));
    QLabel* FC_Label = new QLabel(tr("Show statistics for Fluorinated Compounds Pollutants:"));
    QLabel* CD_Label = new QLabel(tr("See if levels are safe:"));

    OV_Label->setStyleSheet("font-size: 18px;");
    POP_Label->setStyleSheet("font-size: 18px;");
    ELI_Label->setStyleSheet("font-size: 18px;");
    FC_Label->setStyleSheet("font-size: 18px;");
    CD_Label->setStyleSheet("font-size: 18px;");


    // Connect buttons to actions
    QObject::connect(OV_Button, &QPushButton::clicked, this, &Dashboard::onOVButtonClicked);
    QObject::connect(POP_Button, &QPushButton::clicked, this, &Dashboard::onPOPButtonClicked);
    QObject::connect(ELI_Button, &QPushButton::clicked, this, &Dashboard::onELIButtonClicked);
    QObject::connect(FC_Button, &QPushButton::clicked, this, &Dashboard::onFCButtonClicked);
    QObject::connect(CD_Button, &QPushButton::clicked, this, &Dashboard::onCDButtonClicked);


    // Set button styles
    auto setButtonStyle = [](QPushButton* button) {
        button->setFont(QFont("Helvetica", 17, QFont::Bold));
        button->setFixedSize(400, 200); // Adjusted size for spacing
        button->setStyleSheet("background-color: #3C9EFF; color: white; border-radius: 10px");
    };

    setButtonStyle(OV_Button);
    setButtonStyle(POP_Button);
    setButtonStyle(ELI_Button);
    setButtonStyle(FC_Button);
    setButtonStyle(CD_Button);

    // Layout for each button and label pair
    QVBoxLayout* OV_Layout = new QVBoxLayout;
    OV_Layout->addWidget(OV_Label, 0, Qt::AlignCenter);
    OV_Layout->addWidget(OV_Button, 0, Qt::AlignCenter);

    QVBoxLayout* POP_Layout = new QVBoxLayout;
    POP_Layout->addWidget(POP_Label, 0, Qt::AlignCenter);
    POP_Layout->addWidget(POP_Button, 0, Qt::AlignCenter);

    QVBoxLayout* ELI_Layout = new QVBoxLayout;
    ELI_Layout->addWidget(ELI_Label, 0, Qt::AlignCenter);
    ELI_Layout->addWidget(ELI_Button, 0, Qt::AlignCenter);

    QVBoxLayout* FC_Layout = new QVBoxLayout;
    FC_Layout->addWidget(FC_Label, 0, Qt::AlignCenter);
    FC_Layout->addWidget(FC_Button, 0, Qt::AlignCenter);

    QVBoxLayout* CD_Layout = new QVBoxLayout;
    CD_Layout->addWidget(CD_Label, 0, Qt::AlignCenter);
    CD_Layout->addWidget(CD_Button, 0, Qt::AlignCenter);

    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addStretch(); 
    topRow->addLayout(OV_Layout);
    topRow->addStretch(); 
    topRow->addLayout(POP_Layout);
    topRow->addStretch();
    topRow->addLayout(ELI_Layout);
    topRow->addStretch(); 

    QHBoxLayout* bottomRow = new QHBoxLayout;
    bottomRow->addStretch(); 
    bottomRow->addLayout(FC_Layout);
    bottomRow->addStretch(); 
    bottomRow->addLayout(CD_Layout);
    bottomRow->addStretch(); 

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addStretch(); 
    mainLayout->addLayout(topRow);
    mainLayout->addStretch(); 
    mainLayout->addLayout(bottomRow);
    mainLayout->addStretch(); 

    setLayout(mainLayout);
    setMinimumSize(1000, 700);
    setWindowTitle("Water Quality Program");
    showMaximized();
}

void Dashboard::onOVButtonClicked()
{
    PollutantOverviewWindow* newWindow = new PollutantOverviewWindow();
    newWindow->show();
}

void Dashboard::onPOPButtonClicked()
{
    POPWindow* newWindow = new POPWindow();
    newWindow->show();
}

void Dashboard::onELIButtonClicked()
{
    ELIWindow* newWindow = new ELIWindow();
    newWindow->show();
}

void Dashboard::onFCButtonClicked()
{
    FCWindow* newWindow = new FCWindow();
    newWindow->show();
}

void Dashboard::onCDButtonClicked()
{
    PhysicalPage* newWindow = new PhysicalPage();
    newWindow->show();
}
