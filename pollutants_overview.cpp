#include "pollutants_overview.hpp"
#include "sampleset.hpp"

PollutantOverviewWindow::PollutantOverviewWindow(QWidget* parent) : QWidget(parent)
{

    setMinimumSize(1000, 800);
    setWindowTitle("Pollutants Overview");

    QVBoxLayout* pageLayout = new QVBoxLayout;

    // body of water search box layout
    water = new QLineEdit();
    button = new QPushButton("Search", this);
    waterLabel = new QLabel("Body of Water:");
    waterLabel->setBuddy(water);

    form1Layout = new QHBoxLayout();
    form1Layout->addWidget(waterLabel);
    form1Layout->addWidget(water);
    form1Layout->addWidget(button);
    pageLayout->addLayout(form1Layout);

    // table
    table = new QTableWidget(this);
    table->setRowCount(14);
    table->setColumnCount(4);
    QStringList ColumnHeaders;
    ColumnHeaders << "Pollutant Label" << "Avg." << "Min." << "Max.";
    QStringList RowHeaders;
    RowHeaders << "Nitrogen - N" << "C - org filt" << "Phosphorus - P" << "SiO2 Rv"
               << "Ammonia (N)" << "O Diss %sat" << "N oxidised" << "Chloride Ion"
               << "Nitrate - N" << "Nitrite - N" << "Orthophospht" << "Oxygen diss"
               << "Sld sus@105C" << "NH3 un-ion";
    table->setHorizontalHeaderLabels(ColumnHeaders);
    table->setVerticalHeaderLabels(RowHeaders);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pageLayout->addWidget(table);

    // pollutant search
    pollutant = new QComboBox();
    pollutant->addItem("Choose pollutant");
    pollutant->addItems(RowHeaders);
    pollutantLabel = new QLabel("Show graph of:");
    pollutantLabel->setBuddy(pollutant);

    form2Layout = new QHBoxLayout();
    form2Layout->addWidget(pollutantLabel);
    form2Layout->addWidget(pollutant);
    pageLayout->addLayout(form2Layout);

    // time series graph
    series = new QLineSeries();
    series->setPointsVisible(true);

    chart = new QChart();
    chart->addSeries(series);
    
    QDateTimeAxis* Xaxis = new QDateTimeAxis();
    Xaxis->setFormat("yyyy-MM-dd");

    QValueAxis* Yaxis = new QValueAxis();
    Yaxis->setTitleText("Pollutant Level");

    chart->addAxis(Xaxis, Qt::AlignBottom);

    series->attachAxis(Xaxis);

    chart->setTitle("Enter a body of water to start plotting...");

    // set colour for line
    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    series->setPen(pen);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    pageLayout->addWidget(chartView);

    pageLayout->setAlignment(Qt::AlignCenter);

    connect(button, &QPushButton::clicked, this, &PollutantOverviewWindow::populateTable);
    connect(pollutant, &QComboBox::currentTextChanged, this, &PollutantOverviewWindow::plotGraph);

    setLayout(pageLayout);
    showMaximized();
}

void PollutantOverviewWindow::populateTable(){
    // save our water to search for
    bodyOfWater = water->text().trimmed();

    const char* rows[14] = {"Nitrogen - N", "C - org filt", "Phosphorus - P", "SiO2 Rv",
                            "Ammonia (N)", "O Diss %sat", "N oxidised", "Chloride Ion",
                            "Nitrate - N", "Nitrite - N", "Orthophospht", "Oxygen diss",
                            "Sld sus@105C", "NH3 un-ion"};

    // load data
    SampleSet initial_set("../data/Y-2024-M.csv");
    // filter by location
    std::string searched = bodyOfWater.toStdString();
    std::transform(searched.begin(), searched.end(), searched.begin(),::toupper);
    bodyOfWater = QString::fromStdString(searched);
    SampleSet location_set = initial_set.filterLocation(searched);

    // make sure table is clear before populating
    for(int i = 0; i < 14; i++){
        for(int j = 0; j < 4; j++){
            table->takeItem(i, j);
        }
    }

    // rows
    for(int i = 0; i < 14; i++){
        SampleSet pollutant_set = location_set.filterName(rows[i]);
        // find min and max
        if(pollutant_set.sampleSize() > 0){
            
            double min = pollutant_set.sampleAt(0).getLevel();
            double max = 0;
            for(int k = 0; k < pollutant_set.sampleSize(); k++){
                Sample temp = pollutant_set.sampleAt(k);
                double level = temp.getLevel();
                if(level < min){
                    min = level;
                }else if(level > max){
                    max = level;
                }
            }
            // columns
            for(int j = 0; j < 4; j++){
                if(j == 1){
                    QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(pollutant_set.getAvg()));
                    table->setItem(i, j, item);
                    item->setBackground(QBrush(QColor(255, 255, 255)));
                }else if(j == 2){
                    QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(min));
                    table->setItem(i, j, item);
                    item->setBackground(QBrush(QColor(255, 255, 255)));
                }else if(j == 3){
                    QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(max));
                    table->setItem(i, j, item);
                    item->setBackground(QBrush(QColor(255, 255, 255)));
                }
            }
        }else{
            QTableWidgetItem *item = new QTableWidgetItem(QString("No record"));
            table->setItem(i, 0, item);
            for(int j = 1; j < 4; j++){
                QTableWidgetItem *item = new QTableWidgetItem();
                table->setItem(i, j, item);
                item->setBackground(QBrush(QColor(0, 0, 0)));
            }
        }
    }
}

void PollutantOverviewWindow::plotGraph(){
    if(bodyOfWater.length() != 0){
        QString plotPollutant = pollutant->currentText();
        std::string stringPollutant = plotPollutant.toStdString();

        QLineSeries* series = new QLineSeries();
        series->setPointsVisible(true);
        chart->removeAllSeries();

        QList<QAbstractAxis*> axes = chart->axes();
        for (QAbstractAxis* axis : axes){
            chart->removeAxis(axis);
        }
        

        SampleSet initial_set("../data/Y-2024-M.csv");
        // filter by location
        std::string searched = bodyOfWater.toStdString();
        SampleSet location_set = initial_set.filterLocation(searched);
        SampleSet pollutant_set = location_set.filterName(stringPollutant);
        if(pollutant_set.sampleSize() > 0){
            for(int i = 0; i < pollutant_set.sampleSize(); i++){
                Sample point = pollutant_set.sampleAt(i);
                QDateTime time = QDateTime::fromString(QString::fromStdString(point.getTime()), "yyyy-MM-ddTHH:mm:ss");
                series->append(time.toMSecsSinceEpoch(), point.getLevel());
            }
            chart->addSeries(series);

            QDateTimeAxis* Xaxis = new QDateTimeAxis();
            Xaxis->setFormat("yyyy-MM-dd");
            chart->addAxis(Xaxis, Qt::AlignBottom);
            series->attachAxis(Xaxis);

            QValueAxis* Yaxis = new QValueAxis();
            Yaxis->setTitleText("Pollutant Level");

            chart->setTitle(plotPollutant + " levels in " + bodyOfWater);
            chart->addAxis(Yaxis, Qt::AlignLeft);
            series->attachAxis(Yaxis);

            chartView->setChart(chart);
            chartView->update();
        }
    }
}
