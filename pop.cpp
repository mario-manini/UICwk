#include "pop.hpp"
#include <QFont>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget> 
#include <QSpacerItem>
#include <QSizePolicy>
#include <QtCharts>
#include "getLakes.hpp"
#include <iostream>


POPWindow::POPWindow(QWidget* parent) : QWidget(parent)
{
    QString filePath = "../data/testData.csv";  
    int columnIndex = 3;  

    QStringList lakes = ExtractUniqueColumns::extractUniqueColumnItems(filePath, columnIndex);
    QLineSeries* series = new QLineSeries();
    series->append(0, 3);
    series->append(1, 5);

    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("POP Levels Over Time");

    QChartView* chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* headerLabel = new QLabel("Persistent Organic Pollutants", this);
    headerLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    mainLayout->addWidget(headerLabel);

    mainLayout->addWidget(chartview);

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search lakes...");
    searchBar->setFixedWidth(400);
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addStretch();  
    searchLayout->addWidget(searchBar);
    searchLayout->addStretch(); 
    mainLayout->addLayout(searchLayout);

    searchResultsList = new QListWidget(this);
    mainLayout->addWidget(searchResultsList);

    QGroupBox* rolloverGroupBox = new QGroupBox("Rollover Pop-ups: Health Risks & Safety Information", this);
    QVBoxLayout* rolloverLayout = new QVBoxLayout();
    QLabel* rolloverLabel = new QLabel("Hover over the chart to see detailed information on health risks, monitoring importance, and safety levels.", this);
    rolloverLabel->setAlignment(Qt::AlignCenter);
    rolloverLayout->addWidget(rolloverLabel);
    rolloverGroupBox->setLayout(rolloverLayout);
    rolloverGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(rolloverGroupBox);

    QGroupBox* complianceGroup = new QGroupBox("Pollutant Compliance Checker", this);
    QVBoxLayout* complianceLayout = new QVBoxLayout();

    QComboBox* pollutantSelector = new QComboBox(this);
    pollutantSelector->addItems({"Pollutant Example 1", "Pollutant Example 2", "Pollutant Example 3", "Pollutant Example 4"});
    pollutantSelector->setCurrentIndex(0);
    pollutantSelector->setFixedWidth(300);

    complianceLabel = new QLabel(this);
    complianceLabel->setAlignment(Qt::AlignCenter);
    complianceLabel->setWordWrap(true);
    QFont complianceFont = complianceLabel->font();
    complianceFont.setPointSize(14);
    complianceLabel->setFont(complianceFont);
    complianceLabel->setFixedWidth(500);

    updateCompliance(pollutantSelector->currentText());
    connect(pollutantSelector, &QComboBox::currentTextChanged, this, &POPWindow::updateCompliance);

    complianceLayout->addWidget(pollutantSelector, 0, Qt::AlignCenter);
    complianceLayout->addWidget(complianceLabel, 0, Qt::AlignCenter);
    complianceGroup->setLayout(complianceLayout);
    complianceGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mainLayout->addWidget(complianceGroup);

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer);

    setLayout(mainLayout);
    setMinimumSize(800, 600);
    setWindowTitle("Persistent Organic Pollutants (POP)");
    showMaximized();

    connect(searchBar, &QLineEdit::textChanged, this, &POPWindow::handleSearch);
    
}

void POPWindow::updateCompliance(const QString& pollutant)
{
    if (pollutant == "Pollutant Example 1") {
        complianceLabel->setText("Compliant with UK/EU Safety Levels");
        complianceLabel->setStyleSheet("QLabel { color : green; }");
    } else if (pollutant == "Pollutant Example 2") {
        complianceLabel->setText("Non-Compliant");
        complianceLabel->setStyleSheet("QLabel { color : red; }");
    } else if (pollutant == "Pollutant Example 3") {
        complianceLabel->setText("Close to threshold.");
        complianceLabel->setStyleSheet("QLabel { color : orange; }");
    } else {
        complianceLabel->setText("Data not available.");
        complianceLabel->setStyleSheet("QLabel { color : gray; }");
    }
}

void POPWindow::handleSearch(const QString& searchText)
{
    searchResultsList->clear();
    QString filePath = "../data/testData.csv";  
    int columnIndex = 3;  

    QStringList allLakes = ExtractUniqueColumns::extractUniqueColumnItems(filePath, columnIndex);

    QStringList filteredLakes;
    for (const QString& lake : allLakes) {
        if (lake.contains(searchText, Qt::CaseInsensitive)) {
            filteredLakes.append(lake);
        }
    }
    searchResultsList->addItems(filteredLakes);
}




