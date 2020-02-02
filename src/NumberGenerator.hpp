#pragma once 

#include <QObject>

class NumberGenerator: public QObject
{
    Q_OBJECT
public:
    uint32_t GenerateNumber();
public slots:
    void GenerateNumberSlot();
signals:
    void FinishedGenerating(uint32_t result);
};