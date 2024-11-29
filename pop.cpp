#include "pop.hpp"

POPWindow::POPWindow(QWidget* parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("Persistent Organic Pollants Page", this);
    label->setAlignment(Qt::AlignCenter);
    setWindowTitle("Persistent Organic Pollants Page");
    setMinimumSize(700,1000);

}
