#ifndef POLLUTANTOVERVIEW_HPP
#define POLLUTANTOVERVIEW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QHeaderView>

class PollutantOverviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PollutantOverviewWindow(QWidget* parent = nullptr);

private:
    QLineEdit* water;             
    QLabel* waterLabel;          
    QTableWidget* table;           
    QComboBox* pollutant;          
    QLabel* pollutantLabel;         
    QVBoxLayout* pageLayout;      
    QHBoxLayout* form1Layout;       
    QHBoxLayout* form2Layout;      
};

#endif 
