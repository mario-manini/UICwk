#pragma once

#ifndef ELIWINDOW_H
#define ELIWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QScrollArea>
#include "sampleset.hpp"
#include <set>
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
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

class QBarSet;

class ELIWindow : public QWidget {
    Q_OBJECT

public:
    explicit ELIWindow(QWidget* parent = nullptr);
    void loadData() { data = SampleSet("../data/Y-2024-M.csv"); }
    void filterData() { data = data.filterGroup(3); }

private:
    QComboBox *pollutantComboBox, *locationComboBox;
    QVBoxLayout *chartLayout;
    QWidget *container;
    QScrollArea *scrollArea;

    void loadFilters();
    void updateChart();
    void clearCharts();
    void updateLocs(const QString& searchText);

    SampleSet data;
};

#endif 