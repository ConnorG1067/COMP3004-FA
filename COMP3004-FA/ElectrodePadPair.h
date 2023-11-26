#ifndef ELECTRODEPADPAIR_H
#define ELECTRODEPADPAIR_H

#include <vector>
#include "ElectrodePad.h"

using namespace std;

// Meant to hold the two electrodes on the victim
class ElectrodePadPair {
    // Public functions
    public:
        // Constructors
        ElectrodePadPair(ElectrodePad*, ElectrodePad*);

        // Getters
        ElectrodePad* getUpperPad() { return this->upperPad; }
        ElectrodePad* getLowerPad() { return this->lowerPad; }

    // Private member variables
    private:
        // Upper and lower pads
        ElectrodePad* upperPad;
        ElectrodePad* lowerPad;
};
#endif // ELECTODEPADPAIR_H
