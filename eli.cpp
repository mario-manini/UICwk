#include "eli.hpp"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

ELIWindow::ELIWindow(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* headerLabel = new QLabel("Environmental Litter Indicators", this);
    headerLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(headerLabel);

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

    QGroupBox* complianceGroup = new QGroupBox("Compliance Status", this);
    QVBoxLayout* complianceLayout = new QVBoxLayout(complianceGroup);
    complianceLabel = new QLabel("Select a pollutant to see compliance.", this);
    complianceLabel->setStyleSheet("color: green;");
    complianceLayout->addWidget(complianceLabel);
    complianceGroup->setLayout(complianceLayout);
    mainLayout->addWidget(complianceGroup);

    chartLayout = new QVBoxLayout();
    container = new QWidget();
    container->setLayout(chartLayout);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    QLabel* footerLabel = new QLabel("Help | About | Contact", this);
    footerLabel->setStyleSheet("font-size: 12px; text-align: center;");
    mainLayout->addWidget(footerLabel);

    setLayout(mainLayout);

    connect(pollutantComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
    connect(locationComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
    connect(typeComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
}

void ELIWindow::loadPollutants() {
    QString filePath = QDir(QCoreApplication::applicationDirPath()).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() > 1) {
                pollutantComboBox->addItem(fields[1].trimmed());
            }
        }
        file.close();
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }
}

void ELIWindow::loadFilters() {
    QString filePath = QDir(QCoreApplication::applicationDirPath()).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QSet<QString> locations, types;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() > 4) {
                locations.insert(fields[3].trimmed());
                types.insert(fields[4].trimmed());
            }
        }
        file.close();
        foreach (const QString &location, locations)
            locationComboBox->addItem(location);
        foreach (const QString &type, types)
            typeComboBox->addItem(type);
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }
}

void ELIWindow::updateCompliance(const QString& pollutant) {
    QString filePath = QDir(QCoreApplication::applicationDirPath()).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        bool isCompliant = true;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields[1].trimmed() == pollutant && fields[4].trimmed().toLower() == "non-compliant") {
                isCompliant = false;
                break;
            }
        }
        file.close();
        complianceLabel->setText(isCompliant ? "Compliant" : "Non-compliant");
        complianceLabel->setStyleSheet(isCompliant ? "color: green;" : "color: red;");
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }
}

void ELIWindow::updateChart() {
    clearCharts(); // Clear existing charts before adding new ones

    QString selectedPollutant = pollutantComboBox->currentText();
    QString selectedLocation = locationComboBox->currentText();
    QString selectedType = typeComboBox->currentText();

    QString filePath = QDir(QCoreApplication::applicationDirPath()).filePath("data/Y-2024-M.csv");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QMap<QDateTime, double> dataMap;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() > 4 && fields[1] == selectedPollutant && fields[3] == selectedLocation && fields[4] == selectedType) {
                QDateTime date = QDateTime::fromString(fields[0], "yyyy-MM-ddTHH:mm:ss");
                double level = fields[2].toDouble();
                dataMap[date] += level;
            }
        }
        file.close();

        if (dataMap.isEmpty()) {
            QLabel *noDataLabel = new QLabel("No data available for the selected filters.");
            noDataLabel->setAlignment(Qt::AlignCenter);
            noDataLabel->setStyleSheet("font-size: 16px; color: red;");
            chartLayout->addWidget(noDataLabel);
        } else {
            QChart *chart = new QChart();
            QLineSeries *series = new QLineSeries();
            for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
                series->append(it.key().toMSecsSinceEpoch(), it.value());
            }
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("Environmental Data Over Time");

            QChartView *chartView = new QChartView(chart);
            chartLayout->addWidget(chartView);
        }

        updateCompliance(selectedPollutant);
    } else {
        qWarning() << "Unable to open file at:" << filePath;
    }
}

void ELIWindow::clearCharts() {
    QLayoutItem* child;
    while ((child = chartLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = child->widget()) {
            delete widget;
        }
        delete child;
    }
}
