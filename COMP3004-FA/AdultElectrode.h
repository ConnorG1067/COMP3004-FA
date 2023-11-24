#ifndef ADULTELECTRODE_H
#define ADULTELECTRODE_H

#include <QGraphicsRectItem>
#include <QPen>

#include "ElectrodePad.h"

class AdultElectrode : public ElectrodePad{
    public:
        AdultElectrode(int x = 0, int y = 0) : ElectrodePad() {
            this->padRect = new QGraphicsRectItem(x, y, 20, 20);
            this->padRect->setBrush(Qt::transparent);
            this->padRect->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        };
        void sensorDetection() override {};
        QGraphicsRectItem* getPadRect() override { return this->padRect; }
    private:
        QGraphicsRectItem* padRect;
};

#endif // ADULTELECTRODE_H
