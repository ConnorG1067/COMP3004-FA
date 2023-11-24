#ifndef CHILDELECTRODE_H
#define CHILDELECTRODE_H

#include <QGraphicsRectItem>
#include <QPen>

#include "ElectrodePad.h"

class ChildElectrode : public ElectrodePad {
    public:
        ChildElectrode(int x = 0, int y = 0) : ElectrodePad() {
            this->padRect = new QGraphicsRectItem(x, y, 20, 20);
            this->padRect->setBrush(Qt::transparent);
            this->padRect->setPen(QPen(Qt::green, 2, Qt::SolidLine));
        };

        void sensorDetection() override {};
        QGraphicsRectItem* getPadRect() override { return this->padRect; }
    private:
        QGraphicsRectItem* padRect;


};

#endif // CHILDELECTRODE_H
