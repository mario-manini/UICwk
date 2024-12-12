#ifndef FC_HPP
#define FC_HPP

#include "sampleset.hpp"
#include <set>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QListWidget> 
#include <QSpacerItem>
#include <QSizePolicy>
#include <QtCharts>
#include <iostream>
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QPen>

class FCWindow : public QWidget {
    Q_OBJECT
public:
    explicit FCWindow(QWidget* parent = nullptr);
    void loadData() { data = SampleSet("../data/Y-2024-M.csv"); }
    void filterPops() { data = data.filterGroup(1); }
    SampleSet data;

public slots:
    void UpdateChart();

private slots:
    void handleSearchBarLake(const QString& searchText);
    void handleSearchBarPollutant(const QString& searchText);
    void updateSearchBarLake(QListWidgetItem* item);
    void updateSearchBarPollutant(QListWidgetItem* item);

private:
    void updateSearchResults(const QString& searchText, QListWidget* resultsList);
    void populateSearchResults();

    QLineSeries* series;
    QChart* MainChart;
    QChartView* chartview;

    QLineEdit* searchBarLake;
    QLineEdit* searchBarPollutant;

    QListWidget* searchResultsLake;
    QListWidget* searchResultsPollutant;

    QLabel* complianceLabel;

    QLabel* minValue;
    QLabel* maxValue;
    QLabel* avgValue;

    QPushButton* filter_button;
    QLabel* minIndic;
    QLabel* maxIndic;
    QLabel* avgIndic;
};

#endif 
