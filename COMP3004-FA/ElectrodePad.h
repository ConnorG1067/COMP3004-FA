#ifndef ELECTRODEPAD_H
#define ELECTRODEPAD_H

#include <stdlib.h>
#include <QGraphicsRectItem>

// Abstract ElectrodePad
class ElectrodePad {
    // Public functions
    public:
        // Constructors
        ElectrodePad() {};
        // Virtual functions for sensorDetection and a getter for the rect
        virtual void sensorDetection() = 0;
        virtual QGraphicsRectItem* getPadRect() = 0;
    // Private member variables
    private:
};

#endif // ELECTRODEPAD_H
