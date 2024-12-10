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

class ELIWindow : public QWidget {
    Q_OBJECT

public:
    explicit ELIWindow(QWidget* parent = nullptr);

private:
    QComboBox *pollutantComboBox, *locationComboBox, *typeComboBox;
    QLabel *complianceLabel;
    QVBoxLayout *chartLayout;
    QWidget *container;
    QScrollArea *scrollArea;

    void loadPollutants();
    void loadFilters();
    void updateCompliance(const QString& pollutant);
    void updateChart();
    void clearCharts();
};

#endif // ELIWINDOW_H