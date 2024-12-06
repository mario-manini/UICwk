#include "eli.hpp"

ELIWindow::ELIWindow(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* headerLabel = new QLabel("Pollutant Analysis", this);
    headerLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(headerLabel);

    QHBoxLayout* navLayout = new QHBoxLayout();
    QPushButton* buttonPage1 = new QPushButton("Page 1", this);
    QPushButton* buttonPage2 = new QPushButton("Page 2", this);
    QPushButton* buttonPage4 = new QPushButton("Page 4", this);
    navLayout->addWidget(buttonPage1);
    navLayout->addWidget(buttonPage2);
    navLayout->addWidget(buttonPage4);
    mainLayout->addLayout(navLayout);

    QGroupBox* filterGroup = new QGroupBox("Filters", this);
    QVBoxLayout* filterLayout = new QVBoxLayout(filterGroup);
    QComboBox* pollutantComboBox = new QComboBox(this);
    pollutantComboBox->addItem("Select Pollutant");
    pollutantComboBox->addItem("1,1,2-Trichloroethane");
    pollutantComboBox->addItem("Chloroform");
    QSlider* timeSlider = new QSlider(Qt::Horizontal, this);
    timeSlider->setRange(0, 100); 
    timeSlider->setValue(50);

    filterLayout->addWidget(pollutantComboBox);
    filterLayout->addWidget(timeSlider);
    filterGroup->setLayout(filterLayout);
    mainLayout->addWidget(filterGroup);

    QGroupBox* complianceGroup = new QGroupBox("Compliance Status", this);
    QVBoxLayout* complianceLayout = new QVBoxLayout(complianceGroup);
    QLabel* complianceLabel = new QLabel("Compliance Indicator will appear here.", this);
    complianceLabel->setStyleSheet("color: green;");
    complianceLayout->addWidget(complianceLabel);
    complianceGroup->setLayout(complianceLayout);
    mainLayout->addWidget(complianceGroup);

    // Placeholder for Pollutant Data Chart
    QGroupBox* chartGroup = new QGroupBox("Pollutant Trends", this);
    QVBoxLayout* chartLayout = new QVBoxLayout(chartGroup);
    QLabel* chartLabel = new QLabel("Time-series chart placeholder.", this);
    chartLayout->addWidget(chartLabel);
    chartGroup->setLayout(chartLayout);
    mainLayout->addWidget(chartGroup);

    QLabel* footerLabel = new QLabel("Help | About | Contact", this);
    footerLabel->setStyleSheet("font-size: 12px; text-align: center;");
    mainLayout->addWidget(footerLabel);

    setLayout(mainLayout);
    showMaximized();

}
