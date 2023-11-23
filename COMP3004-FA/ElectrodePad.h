#ifndef ELECTRODEPAD_H
#define ELECTRODEPAD_H

#include <stdlib.h>
#include <QGraphicsRectItem>

class ElectrodePad {
    public:
        ElectrodePad() {};
        virtual void sensorDetection() = 0;
        virtual QGraphicsRectItem* getPadRect() = 0;
    private:
};

#endif // ELECTRODEPAD_H
