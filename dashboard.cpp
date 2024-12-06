#include "dashboard.hpp"
#include "pop.hpp"
#include "eli.hpp"

Dashboard::Dashboard(QWidget* parent)
    : QWidget(parent)
{
    // Create buttons
    QPushButton* PO_Button = new QPushButton("Pollutant Overview");
    QPushButton* POP_Button = new QPushButton("Persistent Organic Pollutants");
    QPushButton* ELI_Button = new QPushButton("Environmental Litter Indicators");
    QPushButton* FC_Button = new QPushButton("Fluorinated Compounds");
    QPushButton* CD_Button = new QPushButton("Compliance Dashboards");

    // Create labels
    QLabel* PO_Label = new QLabel("Show statistics of the 25 most common pollutants:");
    QLabel* POP_Label = new QLabel("Show statistics for Persistent Organic Pollutants:");
    QLabel* ELI_Label = new QLabel("Summarise Physical Pollutants such as plastic litter:");
    QLabel* FC_Label = new QLabel("Show statistics for Fluorinated Compounds Pollutants:");
    QLabel* CD_Label = new QLabel("See if levels are safe:");

    // Connect buttons to actions
    QObject::connect(POP_Button, &QPushButton::clicked, this, &Dashboard::onPOPButtonClicked);
    QObject::connect(ELI_Button, &QPushButton::clicked, this, &Dashboard::onELIButtonClicked);

    // Set button styles
    auto setButtonStyle = [](QPushButton* button) {
        button->setFont(QFont("Helvetica", 17, QFont::Bold));
        button->setFixedSize(400, 200); // Adjusted size for spacing
        button->setStyleSheet("background-color: #3C9EFF; color: white; border-radius: 10px");
    };

    setButtonStyle(PO_Button);
    setButtonStyle(POP_Button);
    setButtonStyle(ELI_Button);
    setButtonStyle(FC_Button);
    setButtonStyle(CD_Button);

    // Layout for each button and label pair
    QVBoxLayout* PO_Layout = new QVBoxLayout;
    PO_Layout->addWidget(PO_Label, 0, Qt::AlignCenter);
    PO_Layout->addWidget(PO_Button, 0, Qt::AlignCenter);

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

    // Top row (3 buttons with equal spacing)
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addStretch(); // Spacer before the first button
    topRow->addLayout(PO_Layout);
    topRow->addStretch(); // Spacer between buttons
    topRow->addLayout(POP_Layout);
    topRow->addStretch();
    topRow->addLayout(ELI_Layout);
    topRow->addStretch(); // Spacer after the last button

    // Bottom row (2 buttons with equal spacing)
    QHBoxLayout* bottomRow = new QHBoxLayout;
    bottomRow->addStretch(); // Spacer before the first button
    bottomRow->addLayout(FC_Layout);
    bottomRow->addStretch(); // Spacer between buttons
    bottomRow->addLayout(CD_Layout);
    bottomRow->addStretch(); // Spacer after the last button

    // Main layout to center rows vertically
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addStretch(); // Spacer before top row
    mainLayout->addLayout(topRow);
    mainLayout->addStretch(); // Spacer between top and bottom rows
    mainLayout->addLayout(bottomRow);
    mainLayout->addStretch(); // Spacer after bottom row

    // Set layout
    setLayout(mainLayout);
    setMinimumSize(1000, 700); // Adjusted minimum size
    setWindowTitle("Water Quality Program");
    showMaximized();
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
