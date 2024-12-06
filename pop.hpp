#ifndef POP_HPP
#define POP_HPP

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>  
#include <QListWidget> 

class POPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit POPWindow(QWidget* parent = nullptr);

private slots:
    void updateCompliance(const QString& pollutant);
    void handleSearch(const QString& searchText); 

private:
    QLabel* complianceLabel;
    QLineEdit* searchBar; 
    QListWidget* searchResultsList; 
};

#endif
