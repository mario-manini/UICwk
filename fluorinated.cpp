#include "fluorinated.hpp"
#include "getUniqueItems.hpp"

FCWindow::FCWindow(QWidget* parent) : QWidget(parent)
{
    loadData();
    filterPops();
    series = new QLineSeries();
    series->setPointsVisible(true);  

    MainChart = new QChart();
    MainChart->legend()->hide();
    MainChart->addSeries(series);

    QDateTimeAxis* MainX = new QDateTimeAxis();
    MainX->setTitleText("Date");
    MainX->setFormat("yyyy-MM-dd");
    MainX->setRange(QDateTime::currentDateTime().addDays(-30), QDateTime::currentDateTime().addDays(30)); 
    MainX->setGridLineVisible(false);  
    MainX->setLineVisible(true);       
    MainX->setLinePen(QPen(Qt::black, 2)); 

    QValueAxis* MainY = new QValueAxis();
    MainY->setTitleText("Pollutant Level");
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

    QLabel* headerLabel = new QLabel("Fluorinated Compounds", this);
    headerLabel->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");
    mainLayout->addWidget(headerLabel, 0, Qt::AlignCenter);

    QVBoxLayout* contentLayout = new QVBoxLayout();
    
    contentLayout->addWidget(chartview);

    QHBoxLayout* searchBarsLayout = new QHBoxLayout();

    QVBoxLayout* searchBox1Layout = new QVBoxLayout();
    searchBarLake = new QLineEdit(this);
    searchBarLake->setPlaceholderText("Search lakes...");
    searchResultsLake = new QListWidget(this);
    searchBox1Layout->addWidget(searchBarLake);
    searchBox1Layout->addWidget(searchResultsLake);

    QVBoxLayout* searchBox2Layout = new QVBoxLayout();
    searchBarPollutant = new QLineEdit(this);
    searchBarPollutant->setPlaceholderText("Search pollutants...");
    searchResultsPollutant = new QListWidget(this);
    searchBox2Layout->addWidget(searchBarPollutant);
    searchBox2Layout->addWidget(searchResultsPollutant);

    filter_button = new QPushButton("Filter",this);

    searchBarsLayout->addLayout(searchBox1Layout);
    searchBarsLayout->addLayout(searchBox2Layout);

    contentLayout->addLayout(searchBarsLayout);
    contentLayout->addWidget(filter_button);
    
    mainLayout->addLayout(contentLayout);

    QVBoxLayout* statsContainerLayout = new QVBoxLayout();

    QLabel* statsTitle = new QLabel("Data Statistics", this);
    statsTitle->setAlignment(Qt::AlignCenter);
    statsTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    statsContainerLayout->addWidget(statsTitle);

    QGroupBox* statsGroup = new QGroupBox(this);
    QGridLayout* statsLayout = new QGridLayout();
    statsGroup->setLayout(statsLayout);

    statsContainerLayout->addWidget(statsGroup);
    mainLayout->addLayout(statsContainerLayout);

    QLabel* minLabel = new QLabel("Min Value:", this);
    minValue = new QLabel("N/A", this);
    minIndic = new QLabel("", this);
    QLabel* maxLabel = new QLabel("Max Value:", this);
    maxValue = new QLabel("N/A", this);
    maxIndic = new QLabel("", this);
    QLabel* avgLabel = new QLabel("Average:", this);
    avgValue = new QLabel("N/A", this);
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

    // Create additional information box for health risks, monitoring, and safety levels
    QGroupBox* infoGroupBox = new QGroupBox("Additional Information", this);
    QVBoxLayout* infoLayout = new QVBoxLayout();
    
    QLabel* healthRisksLabel = new QLabel("Health Risks of Fluorides:", this);
    healthRisksLabel->setStyleSheet("font-weight: bold;");
    QLabel* healthRisksContent = new QLabel("Exposure to high levels of fluorides can cause skeletal fluorosis, which means weakened bones and more frequent fractures.", this);
    healthRisksContent->setWordWrap(true);

    QLabel* monitoringImportanceLabel = new QLabel("Importance of Monitoring:", this);
    monitoringImportanceLabel->setStyleSheet("font-weight: bold;");
    QLabel* monitoringImportanceContent = new QLabel("Monitoring thes compounds is important, because although low levels can aid healthy teeth development, too much can be a serious risk.", this);
    monitoringImportanceContent->setWordWrap(true);

    QLabel* safetyLevelsLabel = new QLabel("Safety Levels:", this);
    safetyLevelsLabel->setStyleSheet("font-weight: bold;");
    QLabel* safetyLevelsContent = new QLabel("Safety levels for fluorate compounds are decided at the safe level before damage, typically about 2mg.", this);
    safetyLevelsContent->setWordWrap(true);

    // Add the content to the info box layout
    infoLayout->addWidget(healthRisksLabel);
    infoLayout->addWidget(healthRisksContent);
    infoLayout->addWidget(monitoringImportanceLabel);
    infoLayout->addWidget(monitoringImportanceContent);
    infoLayout->addWidget(safetyLevelsLabel);
    infoLayout->addWidget(safetyLevelsContent);
    
    infoGroupBox->setLayout(infoLayout);
    statsContainerLayout->addWidget(infoGroupBox);

    // Create bottom box with additional content
    QGroupBox* bottomBoxGroup = new QGroupBox("Quick Info", this);
    QVBoxLayout* bottomBoxLayout = new QVBoxLayout();
    
    QLabel* quickInfoLabel = new QLabel("Data Source: ", this);
    quickInfoLabel->setWordWrap(true);
    quickInfoLabel->setText("<b></b> <a href=\"https://environment.data.gov.uk/water-quality/view/download\">Data Source</a>"
                                            "<b></b> <a href=\"https://environment.data.gov.uk/water-quality/view/doc/reference\">Documentation</a>");
    quickInfoLabel->setOpenExternalLinks(true); 
    bottomBoxLayout->addWidget(quickInfoLabel);

    bottomBoxGroup->setLayout(bottomBoxLayout);

    // Create a horizontal layout to place the bottom box and back button
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(bottomBoxGroup);

    // Back button on the bottom-right corner
    QPushButton* backButton = new QPushButton("Back", this);
    backButton->setStyleSheet(
        "background-color: #3C9EFF; "
        "color: white; "
        "border-radius: 15px; "
        "padding: 15px 30px; "
        "font-size: 18px;");
    
    bottomLayout->addWidget(backButton);
    bottomLayout->setStretch(0, 1);  // Ensures the bottom box takes available space
    bottomLayout->setAlignment(backButton, Qt::AlignRight);  // Align back button to the right

    connect(backButton, &QPushButton::clicked, this, &QWidget::close);

    mainLayout->addLayout(bottomLayout);  // Add bottom layout to main layout


    // Add a spacer item to the layout
    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer);

    setLayout(mainLayout);
    setMinimumSize(800, 600);
    setWindowTitle("Fluorinated Compounds");
    showMaximized();

    connect(searchBarLake, &QLineEdit::textChanged, this, &FCWindow::handleSearchBarLake);
    connect(searchBarPollutant, &QLineEdit::textChanged, this, &FCWindow::handleSearchBarPollutant);
    connect(searchResultsLake, &QListWidget::itemClicked, this, &FCWindow::updateSearchBarLake);
    connect(searchResultsPollutant, &QListWidget::itemClicked, this, &FCWindow::updateSearchBarPollutant);
    connect(filter_button, SIGNAL(clicked()), this, SLOT(UpdateChart())); 


    populateSearchResults();

    QString lakeSearchText = searchBarLake->text();
    QString pollutantSearchText = searchBarPollutant->text();
}



void FCWindow::updateSearchBarLake(QListWidgetItem* item)
{
    searchBarLake->setText(item->text());
}

void FCWindow::updateSearchBarPollutant(QListWidgetItem* item)
{
    searchBarPollutant->setText(item->text());
}

void FCWindow::populateSearchResults()
{   
    //Call functions
    handleSearchBarLake("");      
    handleSearchBarPollutant("");
}

void FCWindow::handleSearchBarLake(const QString& searchText)
{
    updateSearchResults(searchText, searchResultsLake);
}

void FCWindow::handleSearchBarPollutant(const QString& searchText)
{
    updateSearchResults(searchText, searchResultsPollutant);
}

void FCWindow::updateSearchResults(const QString& searchText, QListWidget* resultsList)
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
        resultsList->clear();
        for (int i = 0; i < data.deterSize(); ++i) {
            QString pollutantName = QString::fromStdString(data.determinandAt(i).getName());
            if (pollutantName.contains(searchText, Qt::CaseInsensitive)) {
                resultsList->addItem(pollutantName);
            }
        }
    }
}

void FCWindow::UpdateChart() {
    QString lakeSearchText = searchBarLake->text(); 
    QString pollutantSearchText = searchBarPollutant->text();
    SampleSet filtered;

    if (!lakeSearchText.isEmpty()) {
        filtered = data.filterLocation(lakeSearchText.toStdString());
    } 
    if (!pollutantSearchText.isEmpty()) {
        if (filtered.sampleSize() == 0) {
            filtered = data.filterName(pollutantSearchText.toStdString());
        } else {
            filtered = filtered.filterName(pollutantSearchText.toStdString());
        }
    }

    if (filtered.sampleSize() == 0) {
        QMessageBox::warning(this, "No Data Found", "No data found for the selected filters.");
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

    QDateTime minDate;
    QDateTime maxDate;
    bool firstSample = true;

    std::set<QDateTime> dateSet;
    for (int i = 0; i < filtered.sampleSize(); i++) {
        QDateTime sampleDate = QDateTime::fromString(QString::fromStdString(filtered.sampleAt(i).getTime()), "yyyy-MM-ddTHH:mm:ss");
        dateSet.insert(sampleDate); 
    }

    std::vector<QDateTime> dates(dateSet.begin(), dateSet.end());

    std::vector<float> averages;
    float current = filtered.filterDate(dates[0].toString("yyyy-MM-ddTHH:mm:ss").toStdString()).getAvg();
    float min = current;
    float max = current;
    float avg = 0;
    for (int i = 0; i < dates.size(); i++) {
        float current = filtered.filterDate(dates[i].toString("yyyy-MM-ddTHH:mm:ss").toStdString()).getAvg();
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

    if (!dates.empty()) {
        minDate = maxDate = dates[0];
        for (const QDateTime& timestamp : dates) {
            if (timestamp < minDate) minDate = timestamp;
            if (timestamp > maxDate) maxDate = timestamp;
        }
    }

    for (int i = 0; i < dates.size(); i++) {
        QDateTime timestamp = dates[i];
        series->append(timestamp.toMSecsSinceEpoch(), averages[i]);
    }

    minDate = minDate.addDays(-10);
    maxDate = maxDate.addDays(10);

    MainChart->addSeries(series);

    QDateTimeAxis *xAxis = new QDateTimeAxis();
    xAxis->setFormat("yyyy-MM-dd");
    xAxis->setTitleText("Sample Date");
    xAxis->setRange(minDate, maxDate);
    xAxis->setGridLineVisible(false);  
    xAxis->setLineVisible(true);      
    xAxis->setLinePen(QPen(Qt::black, 2));  
    MainChart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);

    QValueAxis *yAxis = new QValueAxis();
    yAxis->setTitleText("Pollutant Level");
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
    MainChart->setTitle(pollutantSearchText + " levels in " + lakeSearchText);
    MainChart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    chartview->setChart(MainChart);
    chartview->update();
}
