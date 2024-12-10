
#ifndef FLUORINATED_HPP
#define FLUORINATED_HPP

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>  
#include <QListWidget> 

class FCWindow : public QWidget
{
    Q_OBJECT

public:gith
    explicit FCWindow(QWidget* parent = nullptr);

private slots:
    void updateCompliance(const QString& pollutant);
    void handleSearch(const QString& searchText); 

private:
    QLabel* complianceLabel;
    QLineEdit* searchBar; 
    QListWidget* searchResultsList; 
};

#endif


/*

 **Fluorinated Compounds Page**
    - **Purpose**: Display levels of **PFAS** and other fluorinated compounds, which are monitored for their environmental persistence.
    - **Key Elements**:
        - **Map or Time-Series Visualisation**: Show distribution of fluorinated compounds across sites, using either a map view with colour-coded markers or time-series charts.
        - **Compliance Indicators**: Use traffic-light colours to indicate levels relative to safety thresholds (e.g., 0.1 µg/L for PFAS).
        - **Rollover Pop-Ups**: Provide contextual information on PFAS persistence and health/environmental implications.

*/