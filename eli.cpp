#include "eli.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QFile>
#include <QTextStream>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QSet>
#include <QCoreApplication>
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

ELIWindow::ELIWindow(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Header
    QLabel* headerLabel = new QLabel("Environmental Litter Indicators", this);
    headerLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(headerLabel);

    // Navigation Buttons
    QHBoxLayout* navLayout = new QHBoxLayout();
    QPushButton* buttonPage1 = new QPushButton("Page 1", this);
    QPushButton* buttonPage2 = new QPushButton("Page 2", this);
    QPushButton* buttonPage4 = new QPushButton("Page 4", this);
    navLayout->addWidget(buttonPage1);
    navLayout->addWidget(buttonPage2);
    navLayout->addWidget(buttonPage4);
    mainLayout->addLayout(navLayout);

    // Filters Section
    QGroupBox* filterGroup = new QGroupBox("Filters", this);
    QVBoxLayout* filterLayout = new QVBoxLayout(filterGroup);
    pollutantComboBox = new QComboBox(this);
    locationComboBox = new QComboBox(this);
    typeComboBox = new QComboBox(this);
    loadPollutants();
    loadFilters();
    filterLayout->addWidget(new QLabel("Pollutant:"));
    filterLayout->addWidget(pollutantComboBox);
    filterLayout->addWidget(new QLabel("Location:"));
    filterLayout->addWidget(locationComboBox);
    filterLayout->addWidget(new QLabel("Type:"));
    filterLayout->addWidget(typeComboBox);
    filterGroup->setLayout(filterLayout);
    mainLayout->addWidget(filterGroup);

    // Compliance Section
    QGroupBox* complianceGroup = new QGroupBox("Compliance Status", this);
    QVBoxLayout* complianceLayout = new QVBoxLayout(complianceGroup);
    complianceLabel = new QLabel("Select a pollutant to see compliance.", this);
    complianceLabel->setStyleSheet("color: green;");
    complianceLayout->addWidget(complianceLabel);
    complianceGroup->setLayout(complianceLayout);
    mainLayout->addWidget(complianceGroup);

    // Chart Section
    QChart* chart = new QChart();
    chartView = new QChartView(chart, this);
    QVBoxLayout* chartLayout = new QVBoxLayout();
    chartLayout->addWidget(chartView);
    QGroupBox* chartGroup = new QGroupBox("Litter Trends", this);
    chartGroup->setLayout(chartLayout);
    mainLayout->addWidget(chartGroup);

    // Footer
    QLabel* footerLabel = new QLabel("Help | About | Contact", this);
    footerLabel->setStyleSheet("font-size: 12px; text-align: center;");
    mainLayout->addWidget(footerLabel);

    setLayout(mainLayout);

    // Connections for updating chart and compliance based on filter selection
    connect(pollutantComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
    connect(locationComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
    connect(typeComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
}

void ELIWindow::loadPollutants() {
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(currentDir).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    
    qDebug() << "Attempting to open file at:" << filePath;
    if (!file.exists()) {
        qWarning() << "File does not exist at path:" << filePath;
        return;
    }
    
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() > 1)  // Assuming pollutant name is in the second column
                pollutantComboBox->addItem(fields[1]);
        }
        file.close();
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }
}

void ELIWindow::loadFilters() {
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(currentDir).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    
    qDebug() << "Attempting to open file at:" << filePath;
    if (!file.exists()) {
        qWarning() << "File does not exist at path:" << filePath;
        return;
    }
    
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QSet<QString> locations, types;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() > 4) {
                locations.insert(fields[3]); // Assuming location is in the fourth column
                types.insert(fields[4]);     // Assuming type is in the fifth column
            }
        }
        foreach (const QString &loc, locations) {
            locationComboBox->addItem(loc);
        }
        foreach (const QString &type, types) {
            typeComboBox->addItem(type);
        }
        file.close();
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }
}

void ELIWindow::updateChart() {
    QString selectedPollutant = pollutantComboBox->currentText();
    QString selectedLocation = locationComboBox->currentText();
    QString selectedType = typeComboBox->currentText();

    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(currentDir).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    
    qDebug() << "Attempting to open file at:" << filePath;
    if (!file.exists()) {
        qWarning() << "File does not exist at path:" << filePath;
        return;
    }
    
    QBarSeries* barSeries = new QBarSeries();
    QPieSeries* pieSeries = new QPieSeries();

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QMap<QString, double> dataMap;  // Key: Date, Value: Litter level
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields[1] == selectedPollutant && fields[3] == selectedLocation && fields[4] == selectedType) {
                QString date = fields[0];  // Assuming date is the first column
                double level = fields[2].toDouble();  // Assuming level is in the third column
                dataMap[date] += level;
            }
        }

        // Populate Bar and Pie Charts
        foreach (const QString &key, dataMap.keys()) {
            QBarSet* set = new QBarSet(key);
            *set << dataMap[key];
            barSeries->append(set);
            pieSeries->append(key, dataMap[key]);
        }

        file.close();
    } else {
        qWarning() << "Unable to open file at:" << filePath;
        return;
    }

    QChart* chart = chartView->chart();
    chart->removeAllSeries();
    if (barSeries->count() > 0) {
        chart->addSeries(barSeries);
    } else {
        chart->addSeries(pieSeries);
    }
    chart->createDefaultAxes();
    chart->setTitle("Trends for " + selectedPollutant + " at " + selectedLocation);

    // Update compliance
    updateCompliance(selectedPollutant);
}

void ELIWindow::updateCompliance(const QString& pollutant) {
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(currentDir).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    
    qDebug() << "Attempting to open file at:" << filePath;
    if (!file.exists()) {
        qWarning() << "File does not exist at path:" << filePath;
        return;
    }

    bool isCompliant = true;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields[1] == pollutant && fields[4].trimmed().toLower() == "non-compliant") {
                isCompliant = false;
                break;
            }
        }
        file.close();
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }

    if (isCompliant) {
        complianceLabel->setText("Compliant");
        complianceLabel->setStyleSheet("color: green;");
    } else {
        complianceLabel->setText("Non-compliant");
        complianceLabel->setStyleSheet("color: red;");
    }
}


