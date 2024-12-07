#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    window->setMinimumSize(1000, 550);
    window->setWindowTitle("Pollutants Overview");

    // body of water search box layout
    QLineEdit* water = new QLineEdit();
    QLabel* waterLabel = new QLabel("Body of Water:");
    waterLabel->setBuddy(water);

    QHBoxLayout* form1Layout = new QHBoxLayout();
    form1Layout->addWidget(waterLabel);
    form1Layout->addWidget(water);

    // table
    QTableWidget* table = new QTableWidget(window);
    table->setRowCount(14);
    table->setColumnCount(5);
    QStringList ColumnHeaders;
    ColumnHeaders << "Pollutant Label" << "Description" << "Avg." << "Min." << "Max.";
    QStringList RowHeaders;
    RowHeaders << "Nitrogen - N" << "C - org filt" << "Phosphorus - P" << "SiO2 Rv"
               << "Ammonia (N)" << "O Diss %sat" << "N oxidised" << "Chloride Ion"
               << "Nitrate - N" << "Nitrite - N" << "Orthophospht" << "Oxygen diss"
               << "Sld sus@105C" << "NH3 un-ion";
    table->setHorizontalHeaderLabels(ColumnHeaders);
    table->setVerticalHeaderLabels(RowHeaders);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // pollutant search
    QComboBox* pollutant = new QComboBox();
    pollutant->addItems(RowHeaders);
    QLabel* pollutantLabel = new QLabel("Show graph of:");
    pollutantLabel->setBuddy(pollutant);

    QHBoxLayout* form2Layout = new QHBoxLayout();
    form2Layout->addWidget(pollutantLabel);
    form2Layout->addWidget(pollutant);
    
    // arrange whole page layout
    QVBoxLayout* pageLayout = new QVBoxLayout;
    pageLayout->addLayout(form1Layout);
    pageLayout->addWidget(table);
    pageLayout->addLayout(form2Layout);
    pageLayout->setAlignment(Qt::AlignCenter);

    window->setLayout(pageLayout);
    window->show();

    return app.exec();
}
