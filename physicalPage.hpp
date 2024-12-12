#pragma once

#include <QWidget>
#include "sampleset.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFont>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QBrush>
#include <QColor>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>

class QComboBox;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QLineEdit;
class QTableWidget;
class QTableWidgetItem;
class QPushButton;
class QListWidget;
class QListWidgetItem;


class PhysicalPage : public QWidget
{
public:
    //constructor
    explicit PhysicalPage(QWidget* parent = nullptr);
    void loadData() { data = SampleSet("../data/Y-2024-M.csv"); }

public slots:
    void addFilters();

private:
    Q_OBJECT
    //methods to create/arrange the widgets on the page
    void createWidgets();
    void arrangeWidgets();
    void showData(SampleSet);
    void updateSearchResults(const QString& searchText, QListWidget* resultsList);

    //layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* searchBarsLayout;
    QVBoxLayout* searchBox1Layout;
    QVBoxLayout* searchBox2Layout;
    QVBoxLayout* tableLayout;
    //widgets
    QLabel* title_label;
    QLineEdit* locationSearch;
    QListWidget* locResults;
    QLineEdit* pollSearch;
    QListWidget* pollResults;
    QPushButton* filter_button;
    QPushButton* back_button;
    QTableWidget* table;

    SampleSet data;

private slots:
    void handleSearchLoc(const QString& searchText);
    void handleSearchPoll(const QString& searchText);
    void updateSearchLoc(QListWidgetItem* item);
    void updateSearchPoll(QListWidgetItem* item);
};