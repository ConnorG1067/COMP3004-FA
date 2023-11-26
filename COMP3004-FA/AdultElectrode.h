#ifndef ADULTELECTRODE_H
#define ADULTELECTRODE_H

#include <QGraphicsRectItem>
#include <QPen>

#include "ElectrodePad.h"

// AdultElectrode inherits from ElectrodePad
class AdultElectrode : public ElectrodePad{
    // Public functions
    public:
        // AdultElectrode constructor x and y values
        AdultElectrode(int x = 0, int y = 0) : ElectrodePad() {
            // Set the rect's properties
            this->padRect = new QGraphicsRectItem(x, y, 20, 20);
            this->padRect->setBrush(Qt::transparent);
            this->padRect->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        };

        // Override the virtual parent functions
        void sensorDetection() override {};
        QGraphicsRectItem* getPadRect() override { return this->padRect; }
    // Private member variables
    private:
        QGraphicsRectItem* padRect;
};

#endif // ADULTELECTRODE_H
