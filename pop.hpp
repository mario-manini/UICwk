#ifndef POP_HPP
#define POP_HPP

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

class POPWindow : public QWidget {
    Q_OBJECT
public:
    explicit POPWindow(QWidget* parent = nullptr);

private slots:
    void handleSearchBarLake(const QString& searchText);
    void handleSearchBarPollutant(const QString& searchText);
    void handleSearchBarTimePeriod(const QString& searchText);
    void updateSearchBarLake(QListWidgetItem* item);
    void updateSearchBarPollutant(QListWidgetItem* item);
    void updateSearchBarTimePeriod(QListWidgetItem* item);

private:
    void updateSearchResults(const QString& searchText, QListWidget* resultsList);
    void populateSearchResults();


    QLineSeries* series;
    QChart* MainChart;
    QChartView* chartview;

    void UpdateChart();

    QLineEdit* searchBarLake;
    QLineEdit* searchBarPollutant;
    QLineEdit* searchBarTimePeriod;
    QGridLayout* statsLayout;
    QListWidget* searchResultsLake;
    QListWidget* searchResultsPollutant;
    QListWidget* searchResultsTimePeriod;

    QLabel* complianceLabel;
};

#endif 
