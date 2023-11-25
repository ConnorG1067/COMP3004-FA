#include "ElectrodePadPair.h"

// Constructs an ElectrodePadPair
ElectrodePadPair::ElectrodePadPair(ElectrodePad* upperPad, ElectrodePad* lowerPad) {
    // Lower and upper pad initalization
    this->upperPad = upperPad;
    this->lowerPad = lowerPad;
}
