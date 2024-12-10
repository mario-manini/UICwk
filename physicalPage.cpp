#include "physicalPage.hpp"
#include "sampleset.hpp"
#include "dashboard.hpp"
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

PhysicalPage::PhysicalPage(QWidget* parent) : QWidget(parent)
{
    createWidgets();  // Create the widgets
    loadData();
    arrangeWidgets(); // Arrange the widgets in the layout
    
}

void PhysicalPage::createWidgets()
{
    //new widgets
    title_label = new QLabel("Compliance Dashboard");
    pollutant_edit = new QLineEdit("Enter pollutant",this);
    label = new QLabel("Pollutant Searched:", this);
    lineEdit = new QLineEdit("Enter location", this);
    table = new QTableWidget(this);
    filter_button = new QPushButton("Filter",this);
    location_label = new QLabel("Location Searched:",this);
    back_button = new QPushButton("Back",this);

    //sets font/allignment
    title_font = new QFont("Arial",30);
    title_label->setFont(*title_font);

    //links box/label/button to their function
    connect(pollutant_edit, &QLineEdit::textChanged, label, &QLabel::setText);
    connect(lineEdit, &QLineEdit::textChanged, location_label, &QLabel::setText);
    connect(filter_button, &QPushButton::clicked, this, &PhysicalPage::addFilters);
    QObject::connect(back_button, SIGNAL(clicked()), this, SLOT(onBackButtonClicked())); 

    //set up table columns
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Compliancy", "Location", "Safe Level"});
    table->setRowCount(4);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PhysicalPage::arrangeWidgets()
{
    //new layouts
    main_layout = new QVBoxLayout(this);
    horiz_layout1 = new QHBoxLayout();
    horiz_layout2 = new QHBoxLayout();
    vertical_layout = new QVBoxLayout();

    //reduce space between vertical boxes
    vertical_layout->setSpacing(0);

    //stop stretching the boxes
    pollutant_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    location_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    //widgets to layouts
    vertical_layout->addWidget(pollutant_edit);
    vertical_layout->addWidget(label);
    vertical_layout->addWidget(lineEdit);
    vertical_layout->addWidget(location_label);
    vertical_layout->addWidget(filter_button);
    vertical_layout->addWidget(back_button);
    
    horiz_layout1->addLayout(vertical_layout);
    horiz_layout1->addWidget(table);

    main_layout->addWidget(title_label);
    main_layout->addLayout(horiz_layout1);

    setLayout(main_layout);
    loadData(); 
    showData(data);
    showMaximized();
}

void PhysicalPage::showData(SampleSet data) {
    table->clearContents();
    std::vector<SampleSet> groups;
    groups.push_back(data.filterGroup(1));
    groups.push_back(data.filterGroup(2));
    groups.push_back(data.filterGroup(3));
    groups.push_back(data.filterGroup(4));

    int count = 0;
    for (int row=0; row<groups.size(); row++) {
        for (int column=0; column<groups[row].sampleSize(); column++) {
            //reads data to items
            Sample temp = groups[row].sampleAt(column);
            QString name = QString::fromStdString(temp.getDeterminand());
            QString location = QString::fromStdString(temp.getLocation());
            QString units = QString::fromStdString(groups[row].determinandAt(0).getUnits());
            QString level_units = QString::number(temp.getLevel(),'f',4) + " " + units;
            QString safe_level = QString::number(groups[row].determinandAt(0).getSafeLevel(),'f',2) + " " + units;

            //reads to an entry then adds entry
            QStringList entry;
            QBrush colour;
            entry << name << level_units << location  << safe_level; 
            table->insertRow(count);

            if (temp.getLevel() > groups[row].determinandAt(0).getSafeLevel()) {
                //sets it to red
                colour = QBrush(QColor(255, 0, 0));
            } else if (temp.getLevel() < groups[row].determinandAt(0).getSafeLevel()) {
                colour = QBrush(QColor(0, 255, 0));
            } else {
                colour = QBrush(QColor(100, 100, 0));
            }

            for (int i = 0; i < entry.size(); i++) {
                QTableWidgetItem *item = new QTableWidgetItem(entry[i]);
                item->setBackground(colour);
                table->setItem(count, i, item);
            }

            count++;
        }
    }
}

void PhysicalPage::addFilters()
{
    SampleSet filtered;
    QString location_filter = location_label->text();

    filtered = data.filterLocation(location_filter.toStdString());
    if (filtered.sampleSize() == 0) {
        location_label->setText("Location doesnt exist");
    }

    QString pollutant_filter = label->text();
    if (filtered.sampleSize() == 0) {
        filtered = data.filterName(pollutant_filter.toStdString());
    } else {
        filtered = filtered.filterName(pollutant_filter.toStdString());
    }


    if (filtered.sampleSize() == 0) {
        label->setText("Pollutant doesnt exist");
    }

    showData(filtered);
}

void PhysicalPage::onBackButtonClicked() {
    Dashboard* newWindow = new Dashboard();
    newWindow->show();
    this->close();
}