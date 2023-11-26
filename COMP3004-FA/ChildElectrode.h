#ifndef CHILDELECTRODE_H
#define CHILDELECTRODE_H

#include <QGraphicsRectItem>
#include <QPen>

#include "ElectrodePad.h"

// Child Electrode inherits from ElectrodePad
class ChildElectrode : public ElectrodePad {
    // Public functions
    public:
        // ChildElectrode constructor x and y values
        ChildElectrode(int x = 0, int y = 0) : ElectrodePad() {
            // Set the rect's properties
            this->padRect = new QGraphicsRectItem(x, y, 20, 20);
            this->padRect->setBrush(Qt::transparent);
            this->padRect->setPen(QPen(Qt::green, 2, Qt::SolidLine));
        };

        // Override the virtual parent functions
        void sensorDetection() override {};
        QGraphicsRectItem* getPadRect() override { return this->padRect; }
    // Private member variables
    private:
        QGraphicsRectItem* padRect;


};

#endif // CHILDELECTRODE_H
