#include "pop.hpp"

POPWindow::POPWindow(QWidget* parent)
    : QWidget(parent)
{
    //PRESENT DATA ON ***PCBs*** and other persistent organic pollutants due to their long-lasting impact on the environment and health
    /*
    
    KEY ELEMENTS:

    Data Trends: Use line charts to show POP levels at various sampling points over time

    Rollover Pop-ups: Include additional Information on health risks, monitoring importance and safety levels.

    Compliance colour coding: Show complicance with UK/EU safety levels using colour coded indicators.    
    
    
    */

    QLabel* label = new QLabel("Persistent Organic Pollants Page", this);
    label->setAlignment(Qt::AlignCenter);
    setWindowTitle("Persistent Organic Pollants Page");
    setMinimumSize(700,1000);

}
