#pragma once
#ifndef ELIWINDOW_H
#define ELIWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>



class ELIWindow : public QWidget {
    Q_OBJECT

public:
    explicit ELIWindow(QWidget* parent = nullptr);

private:
    // UI components
    QComboBox* pollutantComboBox;  // Combo box to select pollutants
    QComboBox* locationComboBox;   // Combo box to select locations
    QComboBox* typeComboBox;       // Combo box to select litter types
    QLabel* complianceLabel;       // Label to show compliance status
    QChartView* chartView;         // Chart view to display litter data trends

    // Methods
    void loadPollutants();          // Loads pollutants into the pollutantComboBox
    void loadFilters();             // Loads locations and types of litter into combo boxes
    void updateCompliance(const QString& pollutant);  // Updates compliance status based on selected pollutant

private slots:
    void updateChart();            // Updates the chart based on selected filters
};

#endif // ELIWINDOW_H
