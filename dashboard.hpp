#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class Dashboard : public QWidget
{
    Q_OBJECT 

public:
  
    Dashboard(QWidget* parent = nullptr);

public slots:
    void onPOPButtonClicked();
    void onELIButtonClicked();
};

#endif 