#include "pop.hpp"
#include "sampleset.hpp"
#include "getUniqueItems.hpp"

POPWindow::POPWindow(QWidget* parent) : QWidget(parent)
{
    series = new QLineSeries();
    series->setPointsVisible(true);  

    MainChart = new QChart();
    MainChart->legend()->hide();
    MainChart->addSeries(series);

    QDateTimeAxis* MainX = new QDateTimeAxis();
    MainX->setTitleText(tr("Date"));
    MainX->setFormat("yyyy-MM-dd");
    MainX->setRange(QDateTime::currentDateTime().addDays(-30), QDateTime::currentDateTime().addDays(30)); 
    MainX->setGridLineVisible(false);  
    MainX->setLineVisible(true);       
    MainX->setLinePen(QPen(Qt::black, 2)); 

    QValueAxis* MainY = new QValueAxis();
    MainY->setTitleText(tr("Pollutant Level"));
    MainY->setRange(0, 30);  
    MainY->setGridLineVisible(false);  
    MainY->setLineVisible(true);      
    MainY->setLinePen(QPen(Qt::black, 2)); 

    MainChart->addAxis(MainX, Qt::AlignBottom);  
    MainChart->addAxis(MainY, Qt::AlignLeft); 

    series->attachAxis(MainX);
    series->attachAxis(MainY);

    chartview = new QChartView(MainChart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartview->setMinimumHeight(400); 

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* headerLabel = new QLabel(tr("Persistent Organic Pollutants"), this);
    headerLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    mainLayout->addWidget(headerLabel, 0, Qt::AlignCenter);

    QVBoxLayout* contentLayout = new QVBoxLayout();
    
    contentLayout->addWidget(chartview);

    QHBoxLayout* searchBarsLayout = new QHBoxLayout();

    QVBoxLayout* searchBox1Layout = new QVBoxLayout();
    searchBarLake = new QLineEdit(this);
    searchBarLake->setPlaceholderText(tr("Search lakes..."));
    searchResultsLake = new QListWidget(this);
    searchBox1Layout->addWidget(searchBarLake);
    searchBox1Layout->addWidget(searchResultsLake);

    QVBoxLayout* searchBox2Layout = new QVBoxLayout();
    searchBarPollutant = new QLineEdit(this);
    searchBarPollutant->setPlaceholderText(tr("Search pollutants..."));
    searchResultsPollutant = new QListWidget(this);
    searchBox2Layout->addWidget(searchBarPollutant);
    searchBox2Layout->addWidget(searchResultsPollutant);

    QVBoxLayout* searchBox3Layout = new QVBoxLayout();
    searchBarTimePeriod = new QLineEdit(this);
    searchBarTimePeriod->setPlaceholderText(tr("Search time period..."));
    searchResultsTimePeriod = new QListWidget(this);
    searchBox3Layout->addWidget(searchBarTimePeriod);
    searchBox3Layout->addWidget(searchResultsTimePeriod);

    searchBarsLayout->addLayout(searchBox1Layout);
    searchBarsLayout->addLayout(searchBox2Layout);
    searchBarsLayout->addLayout(searchBox3Layout);

    contentLayout->addLayout(searchBarsLayout);
    
    mainLayout->addLayout(contentLayout);

    QVBoxLayout* statsContainerLayout = new QVBoxLayout();

    QLabel* statsTitle = new QLabel(tr("Data Statistics"), this);
    statsTitle->setAlignment(Qt::AlignCenter);
    statsTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    statsContainerLayout->addWidget(statsTitle);

    QGroupBox* statsGroup = new QGroupBox(this);
    statsLayout = new QGridLayout();
    statsGroup->setLayout(statsLayout);

    statsContainerLayout->addWidget(statsGroup);
    mainLayout->addLayout(statsContainerLayout);

    QLabel* minLabel = new QLabel(tr("Min Value:"), this);
    minValue = new QLabel(tr("N/A"), this);
    QLabel* maxLabel = new QLabel(tr("Max Value:"), this);
    maxValue = new QLabel("N/A", this);
    QLabel* avgLabel = new QLabel(tr("Average:"), this);
    avgValue = new QLabel(tr("N/A"), this);
    minIndic = new QLabel("", this);
    maxIndic = new QLabel("",this);
    avgIndic = new QLabel("", this);

    statsLayout->addWidget(minLabel, 0, 0);
    statsLayout->addWidget(minValue, 0, 1);
    statsLayout->addWidget(minIndic, 0, 2);
    statsLayout->addWidget(maxLabel, 1, 0);
    statsLayout->addWidget(maxValue, 1, 1);
    statsLayout->addWidget(maxIndic, 1, 2);
    statsLayout->addWidget(avgLabel, 2, 0);
    statsLayout->addWidget(avgValue, 2, 1);
    statsLayout->addWidget(avgIndic, 2, 2);

    QGroupBox* infoGroupBox = new QGroupBox(tr("Additional Information"), this);
    QVBoxLayout* infoLayout = new QVBoxLayout();
    
    QLabel* healthRisksLabel = new QLabel(tr("Health Risks of POPs and PFAS:"), this);
    healthRisksLabel->setStyleSheet("font-weight: bold;");
    QLabel* healthRisksContent = new QLabel(tr("Exposure to POPs, such as PFAS, can lead to serious health risks, including cancer, liver damage, and immune suppression. These chemicals accumulate in the body over time and may cause long-term damage to organs and systems."), this);
    healthRisksContent->setWordWrap(true);

    QLabel* monitoringImportanceLabel = new QLabel(tr("Importance of Monitoring:"), this);
    monitoringImportanceLabel->setStyleSheet("font-weight: bold;");
    QLabel* monitoringImportanceContent = new QLabel(tr("Monitoring POPs and PFAS in water sources and the environment is crucial to prevent contamination of drinking water and ecosystems. It helps track contamination levels and ensure regulatory compliance."), this);
    monitoringImportanceContent->setWordWrap(true);

    QLabel* safetyLevelsLabel = new QLabel(tr("Safety Levels:"), this);
    safetyLevelsLabel->setStyleSheet("font-weight: bold;");
    QLabel* safetyLevelsContent = new QLabel(tr("Safety levels for POPs and PFAS are established to minimize health risks. These levels may vary by country and are subject to change based on new research findings."), this);
    safetyLevelsContent->setWordWrap(true);

    infoLayout->addWidget(healthRisksLabel);
    infoLayout->addWidget(healthRisksContent);
    infoLayout->addWidget(monitoringImportanceLabel);
    infoLayout->addWidget(monitoringImportanceContent);
    infoLayout->addWidget(safetyLevelsLabel);
    infoLayout->addWidget(safetyLevelsContent);
    
        infoGroupBox->setLayout(infoLayout);
    statsContainerLayout->addWidget(infoGroupBox);

    QGroupBox* bottomBoxGroup = new QGroupBox(tr("Quick Info"), this);
    QVBoxLayout* bottomBoxLayout = new QVBoxLayout();
    
    QLabel* quickInfoLabel = new QLabel(tr("Data Source: "), this);
    quickInfoLabel->setWordWrap(true);
    quickInfoLabel->setText("<b></b> <a href=\"https://environment.data.gov.uk/water-quality/view/download\">Data Source</a>"
                                            "<b></b> <a href=\"https://environment.data.gov.uk/water-quality/view/doc/reference\">Documentation</a>");
    quickInfoLabel->setOpenExternalLinks(true); 
    bottomBoxLayout->addWidget(quickInfoLabel);

    bottomBoxGroup->setLayout(bottomBoxLayout);

    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(bottomBoxGroup);


    QPushButton* backButton = new QPushButton(tr("Back"), this);
    backButton->setStyleSheet(
        "background-color: #3C9EFF; "
        "color: white; "
        "border-radius: 15px; "
        "padding: 15px 30px; "
        "font-size: 18px;");
    
    bottomLayout->addWidget(backButton);
    bottomLayout->setStretch(0, 1); 
    bottomLayout->setAlignment(backButton, Qt::AlignRight); 

    connect(backButton, &QPushButton::clicked, this, &QWidget::close);

    mainLayout->addLayout(bottomLayout);  


    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer);

    setLayout(mainLayout);
    setMinimumSize(800, 600);
    setWindowTitle("Persistent Organic Pollutants (POP)");
    showMaximized();

    connect(searchBarLake, &QLineEdit::textChanged, this, &POPWindow::handleSearchBarLake);
    connect(searchBarPollutant, &QLineEdit::textChanged, this, &POPWindow::handleSearchBarPollutant);
    connect(searchBarTimePeriod, &QLineEdit::textChanged, this, &POPWindow::handleSearchBarTimePeriod);
    connect(searchResultsLake, &QListWidget::itemClicked, this, &POPWindow::updateSearchBarLake);
    connect(searchResultsPollutant, &QListWidget::itemClicked, this, &POPWindow::updateSearchBarPollutant);
    connect(searchResultsTimePeriod, &QListWidget::itemClicked, this, &POPWindow::updateSearchBarTimePeriod);

    populateSearchResults();

    QString lakeSearchText = searchBarLake->text();
    QString pollutantSearchText = searchBarPollutant->text();
    QString timePeriodSearchText = searchBarTimePeriod->text();
}



void POPWindow::updateSearchBarLake(QListWidgetItem* item)
{
    searchBarLake->setText(item->text());
    UpdateChart();
}

void POPWindow::updateSearchBarPollutant(QListWidgetItem* item)
{
    searchBarPollutant->setText(item->text());
    UpdateChart();
}

void POPWindow::updateSearchBarTimePeriod(QListWidgetItem* item)
{
    searchBarTimePeriod->setText(item->text());
    UpdateChart();
}

void POPWindow::populateSearchResults()
{   
    //Call functions

    handleSearchBarLake("");      
    handleSearchBarPollutant("");
    handleSearchBarTimePeriod(""); 
}

void POPWindow::handleSearchBarLake(const QString& searchText)
{
    updateSearchResults(searchText, searchResultsLake);
}

void POPWindow::handleSearchBarPollutant(const QString& searchText)
{
    updateSearchResults(searchText, searchResultsPollutant);
}

void POPWindow::handleSearchBarTimePeriod(const QString& searchText)
{
    updateSearchResults(searchText, searchResultsTimePeriod);
}

void POPWindow::updateSearchResults(const QString& searchText, QListWidget* resultsList)
{
    if (resultsList == searchResultsLake){
        resultsList->clear();
        QString filePath = "../data/Y-2024-M.csv";  
        int columnIndex = 3;  

        QStringList allLakes = ExtractUniqueColumns::extractUniqueColumnItems(filePath, columnIndex);

        QStringList filteredLakes;
        for (const QString& lake : allLakes) {
            if (lake.contains(searchText, Qt::CaseInsensitive)) {
                filteredLakes.append(lake);
            }
        }
        resultsList->addItems(filteredLakes);
    }

    if (resultsList == searchResultsPollutant) {
        SampleSet POPs("../data/Y-2024-M.csv");
        SampleSet filteredPOPs = POPs.filterGroup(2);
        resultsList->clear();
        for (int i = 0; i < filteredPOPs.deterSize(); ++i) {
            QString pollutantName = QString::fromStdString(filteredPOPs.determinandAt(i).getName());
            if (pollutantName.contains(searchText, Qt::CaseInsensitive)) {
                resultsList->addItem(pollutantName);
            }
        }
    }

    if (resultsList == searchResultsTimePeriod) {
        resultsList->clear();
        QStringList TimePeriods = {"Last month","Last 3 months","Last 6 months","Last year"};
        
        QStringList filteredTimePeriods;
        for (const QString& timePeriod : TimePeriods) {
            if (timePeriod.contains(searchText, Qt::CaseInsensitive)) {
                filteredTimePeriods.append(timePeriod);
            }
        }
        resultsList->addItems(filteredTimePeriods); 
    }
}

void POPWindow::UpdateChart() {
    QString lakeSearchText = searchBarLake->text().trimmed(); 
    QString pollutantSearchText = searchBarPollutant->text().trimmed();
    QString timePeriodSearchText = searchBarTimePeriod->text().trimmed();

    if (lakeSearchText.isEmpty() || pollutantSearchText.isEmpty() || timePeriodSearchText.isEmpty()) {
        return;
    }

    SampleSet POPs("../data/Y-2024-M.csv");
    SampleSet LocationFiltered = POPs.filterLocation(lakeSearchText.toStdString());
    SampleSet NameFiltered = LocationFiltered.filterName(pollutantSearchText.toStdString());

    if (NameFiltered.sampleSize() == 0) {
        QMessageBox::warning(this, tr("No Data Found"), tr("No data found for the selected filters."));
        return;
    }

    QLineSeries *series = new QLineSeries();
    series->setPointsVisible(true);  
    QPen pen = series->pen();
    pen.setWidth(2);  
    pen.setColor(QColor("#3C9EFF")); 
    series->setPen(pen);

    MainChart->removeAllSeries();
    QList<QAbstractAxis*> axes = MainChart->axes();
    for (QAbstractAxis* axis : axes) {
        MainChart->removeAxis(axis);
    }

    QDateTime maxDate = QDateTime::currentDateTime();
    QDateTime minDate = maxDate;  

    std::set<QDateTime> dateSet;
        for (int i = 0; i < NameFiltered.sampleSize(); i++) {
            QDateTime sampleDate = QDateTime::fromString(QString::fromStdString(NameFiltered.sampleAt(i).getTime()), "yyyy-MM-ddTHH:mm:ss");
            dateSet.insert(sampleDate); 
    }

    std::vector<QDateTime> dates(dateSet.begin(), dateSet.end());

    std::vector<float> averages;
    float current = NameFiltered.filterDate(dates[0].toString("yyyy-MM-ddTHH:mm:ss").toStdString()).getAvg();
    float min = current;
    float max = current;
    float avg = 0;
    for (int i = 0; i < dates.size(); i++) {
        float current = NameFiltered.filterDate(dates[i].toString("yyyy-MM-ddTHH:mm:ss").toStdString()).getAvg();
        if (current < min) { 
            min = current;
        } else if (current > max) {
            max = current;
        }
        averages.push_back(current);
        avg = avg + current;
    }
    
    avg = avg/averages.size();
    minValue->setText(QString::number(min));
    maxValue->setText(QString::number(max));
    avgValue->setText(QString::number(avg));

    if (min > 2) {
        minIndic->setStyleSheet("background-color: red;");
    } else if (min < 2) {
        minIndic->setStyleSheet("background-color: green;");
    } else {
        minIndic->setStyleSheet("background-color: orange;");
    }

    if (max > 2) {
        maxIndic->setStyleSheet("background-color: red;");
    } else if (max < 2) {
        maxIndic->setStyleSheet("background-color: green;");
    } else {
        maxIndic->setStyleSheet("background-color: orange;");
    }

    if (avg > 2) {
        avgIndic->setStyleSheet("background-color: red;");
    } else if (avg < 2) {
        avgIndic->setStyleSheet("background-color: green;");
    } else {
        avgIndic->setStyleSheet("background-color: orange;");
    }


    if (timePeriodSearchText == "Last month") {
        minDate = maxDate.addMonths(-1);
    } else if (timePeriodSearchText == "Last 3 months") {
        minDate = maxDate.addMonths(-3);
    } else if (timePeriodSearchText == "Last 6 months") {
        minDate = maxDate.addMonths(-6);
    } else if (timePeriodSearchText == "Last year") {
        minDate = maxDate.addYears(-1);
    }

    for (int i = 0; i < NameFiltered.sampleSize(); ++i) {
        const Sample& sample = NameFiltered.sampleAt(i);
        QDateTime timestamp = QDateTime::fromString(QString::fromStdString(sample.getTime()), "yyyy-MM-ddTHH:mm:ss");
        series->append(timestamp.toMSecsSinceEpoch(), sample.getLevel());
    }

    MainChart->addSeries(series);

    QDateTimeAxis *xAxis = new QDateTimeAxis();
    xAxis->setFormat("yyyy-MM-dd");
    xAxis->setTitleText(tr("Sample Date"));
    xAxis->setRange(minDate, maxDate);  
    xAxis->setGridLineVisible(false);  
    xAxis->setLineVisible(true);      
    xAxis->setLinePen(QPen(Qt::black, 2));  
    MainChart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);

    QValueAxis *yAxis = new QValueAxis();
    yAxis->setTitleText(tr("Pollutant Level"));
    yAxis->setGridLineVisible(false);  
    yAxis->setLineVisible(true);      
    yAxis->setLinePen(QPen(Qt::black, 2));  

    if (!series->points().isEmpty()) {
        qreal minPollutant = std::numeric_limits<qreal>::max();
        qreal maxPollutant = std::numeric_limits<qreal>::min();
        for (const QPointF& point : series->points()) {
            minPollutant = qMin(minPollutant, point.y());
            maxPollutant = qMax(maxPollutant, point.y());
        }
        yAxis->setRange(minPollutant * 0.95, maxPollutant * 1.05); 
        if (minPollutant < 1) {
            yAxis->setLabelFormat("%.6f");
        } else {
            yAxis->setLabelFormat("%.4f"); 
        }
    }

    MainChart->setTitle(pollutantSearchText + tr(" levels in ") + lakeSearchText + tr(" for the ") + timePeriodSearchText);
    MainChart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    chartview->setChart(MainChart);
    chartview->update();

}
