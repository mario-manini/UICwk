#ifndef POP_HPP
#define POP_HPP

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>  // Include for QLineEdit (search bar)
#include <QListWidget> // Include for QListWidget (search results)

class POPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit POPWindow(QWidget* parent = nullptr);

private slots:
    void updateCompliance(const QString& pollutant);
    void handleSearch(const QString& searchText); // Slot for handling search text

private:
    QLabel* complianceLabel;
    QLineEdit* searchBar; // Member variable for the search bar
    QListWidget* searchResultsList; // Member variable for displaying search results
};

#endif
