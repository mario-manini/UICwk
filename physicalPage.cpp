#include "physicalPage.hpp"
#include "sampleset.hpp"
#include "dashboard.hpp"
#include "getUniqueItems.hpp"


PhysicalPage::PhysicalPage(QWidget* parent) : QWidget(parent)
{
    createWidgets();  // Create the widgets
    loadData();
    arrangeWidgets(); // Arrange the widgets in the layout
    
}

void PhysicalPage::createWidgets()
{
    //set/style title widget
    title_label = new QLabel("Compliance Dashboard",this);
    title_label->setStyleSheet("font-size: 24px; font-weight: bold; text-align: center;");

    //set up search bars for pollutant/lake
    locationSearch = new QLineEdit(this);
    locationSearch->setPlaceholderText("Search locations...");
    locResults = new QListWidget(this);
    locResults->setFixedHeight(200);
    pollSearch = new QLineEdit(this);
    pollSearch->setPlaceholderText("Search pollutants...");
    pollResults = new QListWidget(this);
    pollResults->setFixedHeight(200);

    filter_button = new QPushButton("Filter",this);
    back_button = new QPushButton("Back",this);

    //controls search bars/buttons
    connect(filter_button, SIGNAL(clicked()), this, SLOT(addFilters())); 
    connect(back_button, &QPushButton::clicked, this, &QWidget::close); 
    connect(locationSearch, &QLineEdit::textChanged, this, &PhysicalPage::handleSearchLoc);
    connect(pollSearch, &QLineEdit::textChanged, this, &PhysicalPage::handleSearchPoll);
    connect(locResults, &QListWidget::itemClicked, this, &PhysicalPage::updateSearchLoc);
    connect(pollResults, &QListWidget::itemClicked, this, &PhysicalPage::updateSearchPoll);

    table = new QTableWidget(this);

    //set up table columns
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Name", "Compliancy", "Location", "date", "Safe Level"});
    table->setRowCount(4);
}

void PhysicalPage::arrangeWidgets()
{
    //set up overall layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(title_label, 0, Qt::AlignCenter);
    //layout for the search bars/lists
    searchBarsLayout = new QHBoxLayout();
    searchBox1Layout = new QVBoxLayout();
    searchBox1Layout->addWidget(locationSearch);
    searchBox1Layout->addWidget(locResults);
    searchBox2Layout = new QVBoxLayout();
    searchBox2Layout->addWidget(pollSearch);
    searchBox2Layout->addWidget(pollResults);

    //Add search boxes to layout
    searchBarsLayout->addLayout(searchBox1Layout);
    searchBarsLayout->addLayout(searchBox2Layout);
    mainLayout->addLayout(searchBarsLayout);
    mainLayout->addWidget(filter_button, 0, Qt::AlignCenter);

    //sets table to take as much space as it can
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table->setMinimumHeight(800);
    table->setMinimumWidth(600);
    tableLayout = new QVBoxLayout();
    tableLayout->addWidget(table, 1, Qt::AlignCenter);
    tableLayout->setStretch(1,1);
    mainLayout->addLayout(tableLayout, 1);
  
    setLayout(mainLayout);
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
            QString time = QString::fromStdString(temp.getTime());

            //reads to an entry then adds entry
            QStringList entry;
            QBrush colour;
            entry << name << level_units << location << time << safe_level; 
            table->insertRow(count);

            if (temp.getLevel() > groups[row].determinandAt(0).getSafeLevel()) {
                //sets it to red
                colour = QBrush(QColor(255, 0, 0));
            } else if (temp.getLevel() < groups[row].determinandAt(0).getSafeLevel()) {
                colour = QBrush(QColor(0, 255, 0));
            } else {
                colour = QBrush(QColor(255,140,0));
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
    QString location_filter = locationSearch->text();
    filtered = data.filterLocation(location_filter.toStdString());

    QString pollutant_filter = pollSearch->text();
    if (filtered.sampleSize() == 0) {
        filtered = data.filterName(pollutant_filter.toStdString());
    } else {
        filtered = filtered.filterName(pollutant_filter.toStdString());
    }


    if (filtered.sampleSize() == 0) {
        QMessageBox::warning(this, "No Data Found", "No data found for the selected filters.");
        return;
    }

    showData(filtered);
}

void PhysicalPage::handleSearchLoc(const QString& searchText)
{
    updateSearchResults(searchText, locResults);
}

void PhysicalPage::handleSearchPoll(const QString& searchText)
{
    updateSearchResults(searchText, pollResults);
}

void PhysicalPage::updateSearchLoc(QListWidgetItem* item)
{
    locationSearch->setText(item->text());
}

void PhysicalPage::updateSearchPoll(QListWidgetItem* item)
{
    pollSearch->setText(item->text());
}

void PhysicalPage::updateSearchResults(const QString& searchText, QListWidget* resultsList)
{
    if (resultsList == locResults){
        resultsList->clear();
        QString filePath = "../data/Y-2024-M.csv";  
        int columnIndex = 3;  

        QStringList allLakes = ExtractUniqueColumns::extractUniqueColumnItems(filePath, columnIndex);

        QStringList filteredLakes;
        for (const QString& lake : allLakes) {
            if (lake.contains(searchText, Qt::CaseInsensitive)) {
                filteredLakes.append(lake);
            }
        }
        resultsList->addItems(filteredLakes);
    }

    if (resultsList == pollResults) {
        resultsList->clear();
        for (int i = 0; i < data.deterSize(); ++i) {
            QString pollutantName = QString::fromStdString(data.determinandAt(i).getName());
            if (pollutantName.contains(searchText, Qt::CaseInsensitive)) {
                resultsList->addItem(pollutantName);
            }
        }
    }
}
