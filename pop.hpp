#ifndef POP_HPP
#define POP_HPP

#include <QWidget>
#include <QLabel>
#include <QComboBox>

class POPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit POPWindow(QWidget* parent = nullptr);

private slots:
    void updateCompliance(const QString& pollutant);

private:
    QLabel* complianceLabel;
};

#endif 
