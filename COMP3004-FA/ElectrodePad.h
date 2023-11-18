#ifndef ELECTRODEPAD_H
#define ELECTRODEPAD_H

#include <stdlib.h>

class ElectrodePad {
    public:
        ElectrodePad();
        virtual void sensorDetection() = 0;

        bool getIsOnVictim() { return this->isOnVictim; }
        bool setIsOnVictim() { return this->isOnVictim; }
    private:
        bool isOnVictim = false;
};

#endif // ELECTRODEPAD_H
