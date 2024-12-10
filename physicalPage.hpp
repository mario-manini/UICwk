#pragma once

#include <QWidget>
#include "sampleset.hpp"

class QComboBox;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QLineEdit;
class QTableWidget;
class QTableWidgetItem;
class QPushButton;


class PhysicalPage : public QWidget
{
public:
    //constructor
    explicit PhysicalPage(QWidget* parent = nullptr);
    void loadData() { data = SampleSet("../data/Y-2024-M.csv"); }
    
public slots:
    void onBackButtonClicked();

private:
    Q_OBJECT
    //methods to create/arrange the widgets on the page
    void createWidgets();
    void arrangeWidgets();
    void showData(SampleSet);
    void addFilters();

    QComboBox* comboBox;
    QLabel* label;
    QLineEdit* lineEdit;
    QHBoxLayout* horiz_layout1;
    QHBoxLayout* horiz_layout2;
    QVBoxLayout* vertical_layout;
    QVBoxLayout* main_layout;
    QFont* title_font;
    QLabel* title_label;
    QTableWidget* table;
    QTableWidgetItem* item;
    QPushButton* filter_button;
    QLabel* location_label;
    QLineEdit* pollutant_edit;
    QPushButton* back_button;

    SampleSet data;
};