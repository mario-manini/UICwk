#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSlider>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ELIWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ELIWindow(QWidget* parent = nullptr);
};
