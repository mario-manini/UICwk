#ifndef POLLUTANTOVERVIEW_HPP
#define POLLUTANTOVERVIEW_HPP
#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QHeaderView>
#include <QtCharts>

class PollutantOverviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PollutantOverviewWindow(QWidget* parent = nullptr);

private slots:
    void populateTable();
    void plotGraph();

private:
    QString bodyOfWater;
    QString Pollutant;
    QLineEdit* water;        
    QPushButton* button;     
    QLabel* waterLabel;          
    QTableWidget* table;           
    QComboBox* pollutant;          
    QLabel* pollutantLabel;         
    QVBoxLayout* pageLayout;      
    QHBoxLayout* form1Layout;       
    QHBoxLayout* form2Layout;    
    QLineSeries* series;
    QChart* chart;
    QChartView* chartView;
};

#endif 
