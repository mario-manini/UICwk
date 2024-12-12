#include "eli.hpp"
#include "getUniqueItems.hpp"

ELIWindow::ELIWindow(QWidget* parent) : QWidget(parent) {
    loadData();
    filterData();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* headerLabel = new QLabel(tr("Environmental Litter Indicators"), this);
    headerLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(headerLabel);

    QGroupBox* filterGroup = new QGroupBox("Filters", this);
    QVBoxLayout* filterLayout = new QVBoxLayout(filterGroup);
    pollutantComboBox = new QComboBox(this);
    locationComboBox = new QComboBox(this);
    loadFilters();
    filterLayout->addWidget(new QLabel(tr("Pollutant:")));
    filterLayout->addWidget(pollutantComboBox);
    filterLayout->addWidget(new QLabel(tr("Location:")));
    filterLayout->addWidget(locationComboBox);
    filterGroup->setLayout(filterLayout);
    mainLayout->addWidget(filterGroup);

    chartLayout = new QVBoxLayout();
    container = new QWidget();
    container->setLayout(chartLayout);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    QLabel* footerLabel = new QLabel(tr("Help | About | Contact"), this);
    footerLabel->setStyleSheet("font-size: 12px; text-align: center;");
    mainLayout->addWidget(footerLabel);

    setLayout(mainLayout);

    connect(pollutantComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
    connect(pollutantComboBox, &QComboBox::currentTextChanged, this, &ELIWindow::updateLocs);
    connect(locationComboBox, &QComboBox::currentIndexChanged, this, &ELIWindow::updateChart);
    showMaximized();

}

void ELIWindow::loadFilters() {
    QString filePath = "../data/Y-2024-M.csv";  
    int columnIndex = 3;  

    QStringList allLakes = ExtractUniqueColumns::extractUniqueColumnItems(filePath, columnIndex);

    QStringList filteredLakes;
    for (const QString& lake : allLakes) {
        filteredLakes.append(lake);
    }
    locationComboBox->addItems(filteredLakes);

    std::set<std::string> pollutantSet;
    for (int i=0; i<data.sampleSize(); i++) {
        Sample temp = data.sampleAt(i);
        pollutantSet.insert(temp.getDeterminand());
    }
    for (const auto& pollutant : pollutantSet) {
        pollutantComboBox->addItem(QString::fromStdString(pollutant));
    }
}

void ELIWindow::updateLocs(const QString& searchText) {
    locationComboBox->clear();
    QString filePath = "../data/Y-2024-M.csv"; 
    SampleSet filtered =  data.filterName(searchText.toStdString());
    int columnIndex = 3;  

    QStringList filteredLakes;

    std::set<std::string> locs;
    for (int i=0; i<filtered.sampleSize(); i++) {
        locs.insert(filtered.sampleAt(i).getLocation());
    }

    for (const auto& loc : locs) {
        locationComboBox->addItem(QString::fromStdString(loc));
    }
}

void ELIWindow::updateChart() {
    clearCharts(); // Clear existing charts before adding new ones

    QString selectedPollutant = pollutantComboBox->currentText();
    QString selectedLocation = locationComboBox->currentText();
    
    //call filters
    SampleSet filtered = data.filterName(selectedPollutant.toStdString());
    filtered = data.filterLocation(selectedLocation.toStdString());
    //get set of all times
    std::set<QDateTime> dateSet;
    for (int i=0; i<filtered.sampleSize(); i++) {
        Sample temp = filtered.sampleAt(i);
        dateSet.insert(QDateTime::fromString(QString::fromStdString(temp.getTime()), "yyyy-MM-ddTHH:mm:ss"));
    }
    
    std::vector<QDateTime> dates(dateSet.begin(), dateSet.end());

    std::vector<float> averages;
    QMap<QDateTime, double> dataMap; 
    for (int i = 0; i < dates.size(); i++) {
        float current = filtered.filterDate(dates[i].toString("yyyy-MM-ddTHH:mm:ss").toStdString()).getAvg();
        QDateTime date = dates[i];
        dataMap[date] += current;
    }


    if (dataMap.isEmpty()) {
        QLabel *noDataLabel = new QLabel(tr("No data available for the selected filters."));
        noDataLabel->setAlignment(Qt::AlignCenter);
        noDataLabel->setStyleSheet("font-size: 16px; color: red;");
        chartLayout->addWidget(noDataLabel);
    } else {
        QChart *chart = new QChart();
        QBarSeries *series = new QBarSeries();
        QBarSet *avgset = new QBarSet(tr("Avg set"));
    
        QStringList cats;
        for (auto it = dataMap.begin(); it != dataMap.end(); ++it) { 
            *avgset << it.value(); cats << it.key().toString("yyyy-MM-dd"); 
        }
        series->append(avgset);
        chart->addSeries(series);

        QBarCategoryAxis *axisX = new QBarCategoryAxis(); 
        axisX->append(cats); 
        chart->addAxis(axisX, Qt::AlignBottom); 
        series->attachAxis(axisX); 

        QValueAxis *axisY = new QValueAxis(); 
        axisY->setTitleText(tr("Average Level")); 
        chart->addAxis(axisY, Qt::AlignLeft); 
        series->attachAxis(axisY);

        chart->setTitle(tr("Average Levels over Time"));

        QChartView *chartView = new QChartView(chart);
        chartLayout->addWidget(chartView);
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